#include "Chapter.h"
#include <fmt/core.h>
#include <cpr/api.h>
#include <fstream>
#include <future>
#include <thread>
#include <algorithm>
#include "Sephamore.h"
#include "MIMEType.h"

Chapter Chapter::from_json(const nlohmann::json &json) {
    Chapter chapter;

    chapter.id = json["id"].get<int>();
    chapter.volume = json["volume"].get<std::string>();
    chapter.chapter = json["chapter"].get<std::string>();
    chapter.lang_code = json["lang_code"].get<std::string>();
    chapter.manga_id = json["manga_id"].get<int>();

    //Fix server
    auto raw_server = json["server"].get<std::string>();
    auto server = raw_server[0] == '/' ? "https://mangadex.org" + raw_server : raw_server;


    //Pages
    for (auto &page_url : json["page_array"]) {
        chapter.pages_urls.push_back(server + json["hash"].get<std::string>() + "/" + page_url.get<std::string>());
    }

    return chapter;
}

void Chapter::download_pages(const std::filesystem::path &output_dir, int max_parallel_connection) {

    if (!std::filesystem::exists(output_dir)) {
        std::filesystem::create_directories(output_dir);
    }

    Semaphore semaphore(max_parallel_connection);
    std::vector<std::future<void>> tasks;

    int page = 1;
    for (auto &page_url: pages_urls) {

        tasks.emplace_back(std::async([this, page, &page_url, &output_dir, &semaphore]() {
            ScopedSemaphore _(semaphore);

            fmt::print("Downloading chapter {} page n°{} \n", chapter, page);

            auto response = cpr::Get(cpr::Url{page_url});

            if (response.error || response.status_code != 200) {
                fmt::print(stderr, "Error downloading chapter {} page n°{} skipping\n", chapter, page);
                return;
            }

            auto extension = MIMEType(response.header["Content-Type"]).extension();

            //Save to file
            auto output_path = output_dir / (std::to_string(page) + extension);
            std::ofstream out(output_path, std::ios::binary | std::ios::out);
            out << response.text;
            out.close();

            fmt::print("Done downloading chapter {} page n°{} \n", chapter, page);

        }));
        page++;
    }

    for (std::future<void> &task : tasks) {
        task.wait();
    }

}
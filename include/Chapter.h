#ifndef MANGADEX_DOWNLOADER_CHAPTER_H
#define MANGADEX_DOWNLOADER_CHAPTER_H

#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

struct Chapter {
    int id;
    std::string volume;
    std::string chapter;
    std::string lang_code;
    int manga_id;

    std::vector<std::string> pages_urls;

    static Chapter from_json(const nlohmann::json &);

    void download_pages(const std::filesystem::path &output_dir, int max_parallel_connection = 6);
};



#endif //MANGADEX_DOWNLOADER_CHAPTER_H

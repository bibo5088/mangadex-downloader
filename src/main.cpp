#include <iostream>
#include <algorithm>
#include <fmt/core.h>

#ifdef WIN32

#include <Windows.h>

#endif

#include "Manga.h"
#include "Option.h"

void download_chapter(const PartialChapter &partial_chapter, const std::filesystem::path &output_directory,
                      const int max_parallel_connection) {
    fmt::print("Downloading info for chapter {}\n", partial_chapter.chapter);

    try {
        auto chapter = partial_chapter.get_chapter();

        fmt::print("Done downloading info for chapter {}\n", partial_chapter.chapter);

        chapter.download_pages(output_directory / chapter.chapter, max_parallel_connection);
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what() << "\n";
    }
}


int main(int argc, char **argv) {

#ifdef WIN32
    //Allow more characters on the console
    SetConsoleOutputCP(65001);
#endif

    CLI::App app("Mangadex downloader");
    Option option(app);

    CLI11_PARSE(app, argc, argv)

    try {
        auto manga = Manga::get(option.manga_id);

        fmt::print("Downloading \"{}\"\n", manga.title);

        auto partial_chapters = manga.partial_chapters_by_lang(option.lang_code);

        fmt::print("Found {} chapters in {}\n", partial_chapters.size(), option.lang_code);

        //Download all chapters
        if (option.chapter_name.length() == 0) {
            for (auto &partial_chapter : partial_chapters) {
                download_chapter(partial_chapter, option.output_directory, option.max_parallel_connection);
            }
        }
            //Download a specific chapter
        else {
            auto wanted_partial_chapter = std::find_if(partial_chapters.begin(), partial_chapters.end(),
                                                       [&](PartialChapter &partial_chapter) {
                                                           return partial_chapter.chapter == option.chapter_name;
                                                       });

            if (wanted_partial_chapter == partial_chapters.end()) {
                throw std::runtime_error(fmt::format("Cannot find chapter \"{}\"", option.chapter_name));
            }

            download_chapter(*wanted_partial_chapter, option.output_directory, option.max_parallel_connection);
        }

    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
        return -1;
    }


}


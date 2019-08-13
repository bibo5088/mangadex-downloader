#include <iostream>
#include <fmt/core.h>

#ifdef WIN32

#include <Windows.h>

#endif

#include "Manga.h"
#include "Option.h"

int main(int argc, char **argv) {

#ifdef WIN32
    SetConsoleOutputCP(65001);
#endif

    CLI::App app("Mangadex downloader");
    Option option(app);

    CLI11_PARSE(app, argc, argv);

    try {
        auto manga = Manga::get(option.manga_id);

        fmt::print("Downloading \"{}\"\n", manga.title);

        auto partial_chapters = manga.partial_chapters_by_lang(option.lang_code);

        fmt::print("Found {} chapters in {}\n", partial_chapters.size(), option.lang_code);

        for (auto &partial_chapter : partial_chapters) {
            auto chapter = partial_chapter.get_chapter();
            chapter.download_pages(option.output_directory / chapter.chapter, option.max_parallel_connection);
        }

    }
    catch (std::exception &e) {
        std::cerr << e.what();
    }


}
#ifndef MANGADEX_DOWNLOADER_OPTION_H
#define MANGADEX_DOWNLOADER_OPTION_H

#include <CLI/CLI.hpp>
#include <filesystem>

struct Option {
    explicit Option(CLI::App &app);

    std::string manga_id;
    std::string chapter_name = "";
    std::string lang_code = "gb";
    std::filesystem::path output_directory;
    int max_parallel_connection = 6;
};


#endif //MANGADEX_DOWNLOADER_OPTION_H

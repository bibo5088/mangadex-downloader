#ifndef MANGADEX_DOWNLOADER_MANGA_H
#define MANGADEX_DOWNLOADER_MANGA_H

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "Chapter.h"
#include "PartialChapter.h"

struct Manga {
    std::string id;
    std::string cover_url;
    std::string description;
    std::string title;
    std::string artist;
    std::string author;

    std::vector<PartialChapter> partial_chapters;

    static Manga from_json(const nlohmann::json &);

    static Manga get(const std::string &manga_id);

    std::vector<Chapter> get_chapters(std::string_view lang_code = "gb");

    std::vector<PartialChapter> partial_chapters_by_lang(std::string_view lang_code = "gb");
};

#endif //MANGADEX_DOWNLOADER_MANGA_H

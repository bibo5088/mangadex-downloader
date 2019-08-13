#ifndef MANGADEX_DOWNLOADER_MANGA_H
#define MANGADEX_DOWNLOADER_MANGA_H

#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <exception>
#include <nlohmann/json.hpp>
#include <cpr/error.h>
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


struct MangaException : public std::exception {

    explicit MangaException(const std::string &manga_id, const std::int32_t status_code) : manga_id(manga_id), status_code(status_code){}

    const std::string manga_id;
    const std::int32_t status_code;

};

#endif //MANGADEX_DOWNLOADER_MANGA_H

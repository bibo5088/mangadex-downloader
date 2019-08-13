#include "Manga.h"
#include <algorithm>
#include <thread>
#include <cpr/api.h>
#include <fmt/core.h>

Manga Manga::from_json(const nlohmann::json &json) {
    Manga manga;

    //Manga
    manga.cover_url = "https://mangadex.org" + json["manga"]["cover_url"].get<std::string>();
    manga.description = json["manga"]["description"].get<std::string>();
    manga.title = json["manga"]["title"].get<std::string>();
    manga.artist = json["manga"]["artist"].get<std::string>();
    manga.author = json["manga"]["author"].get<std::string>();

    //Chapters
    for (auto &it : json["chapter"].items()) {
        PartialChapter chapter;

        chapter.id = it.key();
        chapter.chapter = it.value()["chapter"].get<std::string>();
        chapter.title = it.value()["title"].get<std::string>();
        chapter.lang_code = it.value()["lang_code"].get<std::string>();

        manga.partial_chapters.push_back(chapter);
    }

    std::sort(manga.partial_chapters.begin(), manga.partial_chapters.end(),
              [](const PartialChapter &a, const PartialChapter &b) {
                  return std::stod(a.chapter) < std::stod(b.chapter);
              });

    return manga;
}

Manga Manga::get(const std::string &manga_id) {
    auto response = cpr::Get(cpr::Url{"https://mangadex.org/api/manga/" + manga_id});

    return Manga::from_json(nlohmann::json::parse(response.text));
}

std::vector<Chapter> Manga::get_chapters(std::string_view lang_code) {

    std::vector<Chapter> result;

    for (const PartialChapter &chap: partial_chapters) {
        if (chap.lang_code == lang_code) {
            result.push_back(chap.get_chapter());
        }
    }

    return result;
}

std::vector<PartialChapter> Manga::partial_chapters_by_lang(std::string_view lang_code) {

    std::vector<PartialChapter> filtered;

    std::copy_if(partial_chapters.begin(), partial_chapters.end(), std::back_inserter(filtered),
                 [lang_code](const PartialChapter &chap) {
                     return chap.lang_code == lang_code;
                 });

    return filtered;
}



#include <cpr/api.h>
#include <thread>
#include <fmt/core.h>
#include "PartialChapter.h"

Chapter PartialChapter::get_chapter() const {
    
    fmt::print("Downloading info for chapter {}\n", chapter);
    auto response = cpr::Get(cpr::Url{"https://mangadex.org/api/chapter/" + id});
    fmt::print("Done downloading info for chapter {}\n", chapter);

    return Chapter::from_json(nlohmann::json::parse(response.text));
}
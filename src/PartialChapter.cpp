#include <cpr/api.h>
#include <thread>
#include <fmt/core.h>
#include "PartialChapter.h"

Chapter PartialChapter::get_chapter() const {
    

    auto response = cpr::Get(cpr::Url{"https://mangadex.org/api/chapter/" + id});


    return Chapter::from_json(nlohmann::json::parse(response.text));
}
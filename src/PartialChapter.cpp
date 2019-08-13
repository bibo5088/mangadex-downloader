#include <cpr/api.h>
#include <thread>
#include <fmt/core.h>
#include "PartialChapter.h"

Chapter PartialChapter::get_chapter() const {

    auto response = cpr::Get(cpr::Url{"https://mangadex.org/api/chapter/" + id});

    //Errors
    if (response.error) {
        throw std::runtime_error(
                fmt::format("Unable to download info for chapter \"{}\" skipping\n Error : {}", chapter,
                            response.error.message));
    }

    if (response.status_code != 200) {
        throw std::runtime_error(
                fmt::format("Unable to download info for chapter \"{}\" skipping\n Status code : {}", chapter,
                            response.status_code));
    }

    return Chapter::from_json(nlohmann::json::parse(response.text));
}
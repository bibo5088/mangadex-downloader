#ifndef MANGADEX_DOWNLOADER_PARTIALCHAPTER_H
#define MANGADEX_DOWNLOADER_PARTIALCHAPTER_H

#include "Chapter.h"

struct PartialChapter {
    std::string id;
    std::string chapter;
    std::string title;
    std::string lang_code;

    Chapter get_chapter() const;

};


#endif //MANGADEX_DOWNLOADER_PARTIALCHAPTER_H

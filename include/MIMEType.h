#ifndef MANGADEX_DOWNLOADER_MIMETYPE_H
#define MANGADEX_DOWNLOADER_MIMETYPE_H

#include <string_view>
#include <string>

struct MIMEType {
    explicit MIMEType(std::string_view mime_type);

    std::string type;
    std::string name;

    std::string full();

    std::string extension();
};

#endif //MANGADEX_DOWNLOADER_MIMETYPE_H

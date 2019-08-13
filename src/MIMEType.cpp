#include "MIMEType.h"

MIMEType::MIMEType(std::string_view mime_type) {
    std::size_t pos = mime_type.find_first_of('/');
    type = mime_type.substr(0, pos);
    name = mime_type.substr(pos + 1);
}

std::string MIMEType::full() {
    return name + '/' + type;
}

std::string MIMEType::extension() {

    if(name == "svg+xml") {
        return ".svg";
    }

    return '.' + name;
}

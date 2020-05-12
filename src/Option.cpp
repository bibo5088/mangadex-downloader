#include "Option.h"

Option::Option(CLI::App &app) {

    app.add_option("-m, --manga", manga_id, "Mangadex id of the manga")
            ->required(true);

    app.add_option("-c, --chapter", chapter_name, "Name of the chapter. Leave blank for all chapters");

    app.add_option("-o, --output", output_directory, "Output directory")
            ->required(true);

    app.add_option("-l, --lang", lang_code, "Lang code", true);

    app.add_option("-p, --parallel", max_parallel_connection, "Maximum number of parallel connection", true)
            ->check(CLI::Range(1, 10));
}

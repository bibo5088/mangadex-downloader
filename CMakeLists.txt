cmake_minimum_required(VERSION 3.14)
project(mangadex_downloader)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

set(SOURCE_FILES src/main.cpp
        src/Manga.cpp
        src/PartialChapter.cpp
        src/Chapter.cpp
        src/Sephamore.cpp
        src/Option.cpp
        src/MIMEType.cpp)

add_executable(mangadex_downloader ${SOURCE_FILES})
target_include_directories(mangadex_downloader PRIVATE include)
target_link_libraries(mangadex_downloader PRIVATE cpr nlohmann_json::nlohmann_json fmt::fmt CLI11::CLI11)
target_compile_definitions(mangadex_downloader PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
#Warnings
target_compile_options(mangadex_downloader PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall>
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4>)


#Install
include(GNUInstallDirs)
install(TARGETS mangadex_downloader
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
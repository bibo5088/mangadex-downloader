# mangadex-downloader
A command line mangadex downloader

# Usage
Example :
 ```
mangadex_downloader -m 27153 -o manga/jojo-part1/ -p 6 -l gb
 ```

`-m, --manga` The mangadex ID of the manga (https://mangadex.org/title/[ID]/)  
`-o, --output` Output directory  
`-l, --lang` Language of the chapter, lang code used by mangadex (gb for english, fr for french...) Default : gb  
`-p, --parallel` Max number of request done in parallel while downloading pages (1-10) Default : 6  


# Building
Build it like any other cmake project
 ```
cd building-dir-of-choice/
cmake project-dir/
cmake --build
 ```

## Dependencies
* [cpr](https://github.com/whoshuu/cpr) (and it's dependencies)
* [nlohmann_json](https://github.com/nlohmann/json)
* [{fmt}](https://github.com/fmtlib/fmt)
* [CLI11](https://github.com/CLIUtils/CLI11)

### Installing them with [vcpkg](https://github.com/microsoft/vcpkg)
```
vcpkg install cpr nlohmann-json fmt cli11
```


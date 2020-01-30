#include "../include/config.hpp"

#include <fstream>
#include <cstring>

#if defined(linux) || defined(__linux)
    #define PATH  strcat(getenv("HOME"),"/.config/marshmallow_gif.cfg")
#elif defined(_WIN32) || defined (_WIN64)
    #define PATH ""
#else
    #define PATH ""
#endif

bool search_cfg(){
    std::ifstream cfg;

    cfg.open(PATH);

    return cfg.is_open();
}
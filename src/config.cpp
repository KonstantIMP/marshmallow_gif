#include "../include/config.hpp"

#include <fstream>
#include <cstring>
#include <cstdio>

#if defined(linux) || defined(__linux)
    #define CFG_PATH  strcat(getenv("HOME"),"/.config/marshmallow_gif.txt")
#elif defined(_WIN32) || defined (_WIN64)
    #define CFG_PATH ""
#else
    #define CFG_PATH ""
#endif

bool search_cfg(){
    std::ifstream cfg(CFG_PATH);

    return cfg.is_open();
}

bool delete_cfg(){
    if(remove(CFG_PATH) == 0) return true;
    else return false;
}
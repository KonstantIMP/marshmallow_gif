#include "../include/config.hpp"

#include <gtk/gtk.h>

#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>

#if defined(linux) || defined(__linux)
    #define CFG_PATH  "marshmallow_gif.txt"
#elif defined(_WIN32) || defined (_WIN64)
    #define CFG_PATH ""
#else
    #define CFG_PATH ""
#endif

bool search_cfg(){
    std::ifstream cfg_file(CFG_PATH);

    return cfg_file.is_open();
}

bool delete_cfg(){
    if(remove(CFG_PATH) == 0) return true;
    else return false;
}

void create_cfg(std::string theme,
                std::string language,
                std::string easter_en,
                std::string last_file_mode,
                std::string lot_file_mode,
                std::string auto_update){
    std::ofstream cfg(CFG_PATH, std::ios_base::trunc);

    cfg << "[PROGRAMM]\n";

    if(theme == "sys" || theme == STANDART) cfg << "theme=system\n";
    else if(theme == "marsh") cfg << "theme=marshmallow\n";
    else cfg << "theme=oranje\n";

    if(language == "ru") cfg << "language=ru\n";
    else cfg << "language=en\n";

    cfg << "\n";

    cfg << "[FILE]\n";

    if(last_file_mode == "remove" || last_file_mode == STANDART) cfg << "last_file=remove\n";
    else cfg << "last_file=remember\n";

    if(lot_file_mode == "last" || lot_file_mode == STANDART) cfg << "lot_file=last\n";
    else cfg << "lot_file=reopen\n";

    cfg << "\n";

    cfg << "[ANOTHER]\n";

    if(easter_en == STANDART) cfg << "easter=dis\n";
    else cfg << "easter=en\n";

    if(auto_update == STANDART || auto_update == "dis") cfg << "update=dis\n";
    else if(auto_update == "ask") cfg << "update=ask";
    else cfg << "update=auto";

    cfg.close();
}

std::string get_param(char param_num){
    if(!(search_cfg())) return "Config wasn`t defined";

    std::ifstream cfg(CFG_PATH);

    std::string tmp;

    while(getline(cfg, tmp)){
        switch(param_num){
            case THEME:
                if(tmp.substr(0, 5) == "theme"){
                    cfg.close();
                    return tmp.substr(6, tmp.length() - 6); 
                }
                break;
            case LANG:
                if(tmp.substr(0, 8) == "language"){
                    cfg.close();
                    return tmp.substr(9, tmp.length() - 9);
                }
                break;
            case EGGS:
                if(tmp.substr(0, 6) == "easter"){
                    cfg.close();
                    return tmp.substr(7, tmp.length() - 7);
                }
                break;
            case LAST:
                if(tmp.substr(0, 9) == "last_file"){
                    cfg.close();
                    return tmp.substr(10, tmp.length() - 10);
                }
                break;
            case LOTS:
                if(tmp.substr(0, 8) == "lot_file"){
                    cfg.close();
                    return tmp.substr(9, tmp.length() - 9);
                }
                break;
            default:
                if(tmp.substr(0, 6) == "update"){
                    cfg.close();
                    return tmp.substr(7, tmp.length() - 7);
                }
                break;
        }
    }

    cfg.close();

    return "Param wasn`t defined";
}

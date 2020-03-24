#include "../include/config.hpp"
#include "../include/init.hpp"

#include "../include/gtk_start_setup.hpp"
#include "../include/gtk_app.hpp"

#if defined(linux) || defined(__linux)
    std::string OS = "linux";
#elif defined(_WIN32) || defined (_WIN64)
    std::string OS = "windows";
#else
    std::string OS = "mac_os"
#endif

int app_init(int * argc, char *** argv){
    if(!(search_cfg())){
        if(OS == "windows" && OS != "mac_os"){
            //QT ui and warning
        }
        else {
            gtk_app_init(argc, argv);

            gtk_start_setup();
        }
       if(!(search_cfg())) return 2;
    }

    if(get_param(GUI) == "gtk") gtk_app_init(argc, argv);

    return 0;
}

int start_app(queue<std::string> gif_queue){
     if(get_param(GUI) == "gtk") gtk_start_app(gif_queue);


    return 0;
}

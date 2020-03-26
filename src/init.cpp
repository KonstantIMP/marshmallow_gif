#include "../include/config.hpp"
#include "../include/init.hpp"

#include "../include/gtk_start_setup.hpp"
#include "../include/gtk_app.hpp"

#include "../include/qt_start_setup.hpp"
#include "../include/qt_mainwindow.hpp"
#include <QApplication>

#if defined(linux) || defined(__linux)
    std::string OS = "linux";
#elif defined(_WIN32) || defined (_WIN64)
    std::string OS = "windows";
#else
    std::string OS = "mac_os"
#endif

int app_init(int * argc, char *** argv){
    if(!(search_cfg())){
        if(OS == "windows" || OS == "mac_os"){
            QApplication start_setup(*argc, *argv);

            qt_start_setup start_win;
            start_win.show();

            while(start_setup.exec());
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

int start_app(std::string gif_queue, int * argc, char *** argv){
    if(get_param(GUI) == "gtk") gtk_start_app(gif_queue);
    else{
        QApplication main_win(*argc, *argv);

        MainWindow win;
        win.show();

        if(gif_queue != ""){
            if(get_param(LOTS) == "last") win.load_from_file(gif_queue);
            else{
                //will be latest
            }
        }

        while(main_win.exec());
    }

    return 0;
}

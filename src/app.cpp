#include "../include/start_setup.hpp"
#include "../include/config.hpp"
#include "../include/app.hpp"

#include <gtk/gtk.h>

int app_init(int *argc, char ***argv){
    gtk_init(argc, argv);

    if(!(search_cfg())){
        start_setup();

        if(!(search_cfg())) return 2;
    }

    return 0;
}
#include "../include/start_setup.hpp"
#include "../include/config.hpp"
#include "../include/app.hpp"

#include <gtk/gtk.h>

int app_init(int *argc, char ***argv){
    gtk_init(argc, argv);

    if(!(search_cfg())){
        start_setup();
    }
    return 0;
}
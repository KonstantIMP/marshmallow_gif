#include "../include/start_setup.hpp"

#define START_SETUP_FORM "form/start_setup.glade"

#include <gtk/gtk.h>


GtkWidget * window;

// -------------------- Создание окна первичных настроек ----------------------

static GtkWidget * create_window(){
    GtkWidget * setup_win;

    GtkBuilder * setup_win_builder;

    GError * err_msg = NULL;

    setup_win_builder = gtk_builder_new();

    if(!(gtk_builder_add_from_file(setup_win_builder, START_SETUP_FORM, &err_msg))){
        g_critical("Unable to load form file %s", err_msg->message);

        g_error_free(err_msg);

        exit(10);
    }

    gtk_builder_connect_signals(setup_win_builder, NULL);

    setup_win = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "setup_win"));

    if(!(setup_win)){
        g_critical("Unable to load window");

        exit(11);
    }

    g_object_unref(setup_win_builder);

    gtk_container_set_border_width(GTK_CONTAINER(setup_win), 7);

    return setup_win;
}

// -------------------- Функция обработчик окна настроек ----------------------

void start_setup(){
    window = create_window();

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show(window);

    gtk_main();
}
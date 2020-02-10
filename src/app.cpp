#include "../include/start_setup.hpp"
#include "../include/config.hpp"
#include "../include/app.hpp"

#define MAIN_WIN_FROM "form/main_win.glade"

#define SYSTEM_THEME "style/main_system.css"
#define MARSH_THEME "style/main_marshmallow.css"
#define OR_THEME "style/main_oranje.css"

#include <gtk/gtk.h>
#include <string>

// -------------------- Прототипы функций --------------------

static GtkWidget * create_main_window();

void connect_main_css();

// -------------------- Объекты окна --------------------

GtkWidget * main_window;

GtkWidget * exit_btn;
GtkWidget * option_btn;
GtkWidget * open_btn;
GtkWidget * play_btn;
GtkWidget * prev_image_btn;
GtkWidget * next_image_btn;
GtkWidget * speed_down_btn;
GtkWidget * speed_up_btn;
GtkWidget * speed_re_btn;

GtkWidget * speed_pointer_msg;
GtkWidget * speed_indicator_msg;

GtkWidget * gif_place;

GtkCssProvider * main_css;

// -------------------- Инициализация приложения --------------------

int app_init(int *argc, char ***argv){
    gtk_init(argc, argv);

    if(!(search_cfg())){
        start_setup();

        if(!(search_cfg())) return 2;
    }

    // ---------- will be latest ----------
        //if(get_param(UPDATE) == "en"){
          //  update_programm();
        //}
    // ------------------------------------

    return 0;
}

// -------------------- Запуск приложения --------------------

int start_app(queue<std::string> gif_queue){
    main_window = create_main_window();

    gtk_widget_show(main_window);

    gtk_main();

    return 0;
}

// -------------------- Создание окна программы ----------------------

static GtkWidget * create_main_window(){
    GtkWidget * main_win;

    GtkBuilder * main_win_builder;

    GError * err_msg = NULL;

    main_win_builder = gtk_builder_new();

    if(!(gtk_builder_add_from_file(main_win_builder, MAIN_WIN_FROM, &err_msg))){
        g_critical("Unable to load form file %s", err_msg->message);

        g_error_free(err_msg);

        exit(20);
    }

    gtk_builder_connect_signals(main_win_builder, NULL);

    main_win = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "main_win"));

    gtk_window_set_icon_from_file(GTK_WINDOW(main_win), "image/candy.png", NULL);
    gtk_window_set_title(GTK_WINDOW(main_win), "marshmallow_gif");

    if(!(main_win)){
        g_critical("Unable to load window");

        exit(21);
    }

    exit_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "exit"));
    option_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "option"));
    open_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "open"));
    play_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "play"));
    prev_image_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "prev_image"));
    next_image_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "next_image"));
    speed_down_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_down"));
    speed_up_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_up"));
    speed_re_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_re"));

    speed_pointer_msg = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_pointer"));
    speed_indicator_msg = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_indicator"));

    gif_place = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "gif_place"));

    connect_main_css();

    gtk_widget_set_name(GTK_WIDGET(main_win), "main_win");

    g_signal_connect(G_OBJECT(main_win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(main_win_builder);

    return main_win;
}

// -------------------- Подключение стилей ----------------------

void connect_main_css(){
    main_css = gtk_css_provider_new();

    if(get_param(THEME) == "system") gtk_css_provider_load_from_path(main_css, SYSTEM_THEME, NULL);
    else if(get_param(THEME) == "marshmallow") gtk_css_provider_load_from_path(main_css, MARSH_THEME, NULL);
    else gtk_css_provider_load_from_path(main_css, OR_THEME, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(main_css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_set_name(GTK_WIDGET(exit_btn), "exit");
    gtk_widget_set_name(GTK_WIDGET(option_btn), "option");
    gtk_widget_set_name(GTK_WIDGET(open_btn), "open");
    gtk_widget_set_name(GTK_WIDGET(play_btn), "play");
    gtk_widget_set_name(GTK_WIDGET(prev_image_btn), "prev_image");
    gtk_widget_set_name(GTK_WIDGET(next_image_btn), "next_image");
    gtk_widget_set_name(GTK_WIDGET(speed_down_btn), "speed_down");
    gtk_widget_set_name(GTK_WIDGET(speed_up_btn), "speed_up");
    gtk_widget_set_name(GTK_WIDGET(speed_re_btn), "speed_re");

    gtk_widget_set_name(GTK_WIDGET(speed_pointer_msg), "speed_pointer");
    gtk_widget_set_name(GTK_WIDGET(speed_indicator_msg), "speed_indicator");

    gtk_widget_set_name(GTK_WIDGET(gif_place), "gif_place");
}
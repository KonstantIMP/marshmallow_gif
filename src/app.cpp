#include "../include/start_setup.hpp"
#include "../include/setting.hpp"
#include "../include/config.hpp"
#include "../include/gif.hpp"
#include "../include/app.hpp"

#define MAIN_WIN_FROM "form/main_win.glade"

#define SYSTEM_THEME "style/main_system.css"
#define MARSH_THEME "style/main_marshmallow.css"
#define OR_THEME "style/main_oranje.css"

#include <Magick++.h> 
#include <gtk/gtk.h>
#include <string>

// -------------------- Прототипы функций --------------------

static GtkWidget * create_main_window();

void connect_main_css();

void set_text_by_lang();

void signals_connect();

void open_gif();

void size_changed();

void set_icons();

void reset_speed();

void decrement_speed();

void increment_speed();

void change_status();

void frame_plus();

void frame_minus();

void pp_btn_icon();

void setting_programm();

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

GtkWidget * sep_label;

GtkWidget * speed_pointer_msg;
GtkWidget * speed_indicator_msg;

GtkWidget * gif_place;

GtkCssProvider * main_css;

gif_viewer gif_animation;

// -------------------- Инициализация приложения --------------------

int app_init(int *argc, char ***argv){
    gtk_init(argc, argv);

    Magick::InitializeMagick(**argv);

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

    if(gif_queue.get_size() != 0){
        if(gif_queue.get_size() == 1) gif_animation.open_file(gif_queue.dequeue());
        else{
            if(get_param(LOTS) == "last") gif_animation.open_file(gif_queue.dequeue());
            else{
                //Реализую позже
            }
        }
    }

    gif_animation.set_place(gif_place);
    gif_animation.smart_resize();

    gtk_widget_show(main_window);

    gtk_main();

    g_object_unref(main_window);

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

    if(!(main_win)){
        g_critical("Unable to load window");

        exit(21);
    }

    gtk_window_set_icon_from_file(GTK_WINDOW(main_win), "image/candy.png", NULL);
    gtk_window_set_title(GTK_WINDOW(main_win), "marshmallow_gif");

    exit_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "exit"));
    option_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "option"));
    open_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "open"));
    play_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "play"));
    prev_image_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "prev_image"));
    next_image_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "next_image"));
    speed_down_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_down"));
    speed_up_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_up"));
    speed_re_btn = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_re"));

    sep_label = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "sep_label"));

    speed_pointer_msg = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_pointer"));
    speed_indicator_msg = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "speed_indicator"));

    gif_place = GTK_WIDGET(gtk_builder_get_object(main_win_builder, "gif_place"));

    connect_main_css();

    signals_connect();

    set_text_by_lang();

    set_icons();

    gtk_window_set_default_size(GTK_WINDOW(main_win), -1, -1);
    gtk_window_set_resizable(GTK_WINDOW(main_win), TRUE);

    gtk_widget_set_name(GTK_WIDGET(main_win), "main_win");

    g_signal_connect(G_OBJECT(main_win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_WIDGET(main_win), "size-allocate", G_CALLBACK(size_changed), NULL);

    g_object_unref(main_win_builder);
    g_object_unref(main_css);
    if(err_msg != NULL) g_error_free(err_msg);

    gtk_container_set_border_width(GTK_CONTAINER(main_win), 5);

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

    gtk_widget_set_name(GTK_WIDGET(sep_label), "sep_label");

    gtk_widget_set_name(GTK_WIDGET(speed_pointer_msg), "speed_pointer");
    gtk_widget_set_name(GTK_WIDGET(speed_indicator_msg), "speed_indicator");

    gtk_widget_set_name(GTK_WIDGET(gif_place), "gif_place");
}

// -------------------- Установка языка ----------------------

void set_text_by_lang(){
    if(get_param(LANG) == "ru"){
        gtk_button_set_label(GTK_BUTTON(open_btn), "Открыть");

        gtk_label_set_text(GTK_LABEL(speed_pointer_msg), "Скорость");
        gtk_label_set_text(GTK_LABEL(speed_indicator_msg), "100 %");
    }
    else{
        gtk_button_set_label(GTK_BUTTON(open_btn), "Open");

        gtk_label_set_text(GTK_LABEL(speed_pointer_msg), "Speed");
        gtk_label_set_text(GTK_LABEL(speed_indicator_msg), "100 %");
    }

    gtk_label_set_xalign(GTK_LABEL(speed_pointer_msg), 0.08);

    gtk_label_set_xalign(GTK_LABEL(speed_indicator_msg), 0.92);
}

// -------------------- Обработка нажатий ----------------------

void signals_connect(){
    g_signal_connect(G_OBJECT(speed_re_btn), "clicked", G_CALLBACK(reset_speed), NULL);
    g_signal_connect(G_OBJECT(speed_down_btn), "clicked", G_CALLBACK(decrement_speed), NULL);
    g_signal_connect(G_OBJECT(speed_up_btn), "clicked", G_CALLBACK(increment_speed), NULL);
    g_signal_connect(G_OBJECT(exit_btn), "clicked", G_CALLBACK(exit), NULL);
    g_signal_connect(G_OBJECT(open_btn), "clicked", G_CALLBACK(open_gif), NULL);
    g_signal_connect(G_OBJECT(play_btn), "clicked", G_CALLBACK(change_status), NULL);
    g_signal_connect(G_OBJECT(next_image_btn), "clicked", G_CALLBACK(frame_plus), NULL);
    g_signal_connect(G_OBJECT(prev_image_btn), "clicked", G_CALLBACK(frame_minus), NULL);
    g_signal_connect(G_OBJECT(option_btn), "clicked", G_CALLBACK(setting_programm), NULL);
}

// -------------------- Открытие gif анимации --------------------

void open_gif(){
    GtkWidget *dialog;
    GtkFileFilter *filter;

    if(get_param(LANG) == "ru") dialog = gtk_file_chooser_dialog_new("Выберите файл:", GTK_WINDOW(main_window),
                                                                     GTK_FILE_CHOOSER_ACTION_OPEN, ("_Отмена"),
                                                                     GTK_RESPONSE_CANCEL, ("_Открыть"),
                                                                     GTK_RESPONSE_ACCEPT, NULL);
    else dialog = gtk_file_chooser_dialog_new("Choose gif:", GTK_WINDOW(main_window),
                                              GTK_FILE_CHOOSER_ACTION_OPEN, ("_Cancel"),
                                              GTK_RESPONSE_CANCEL, ("_Open"),
                                              GTK_RESPONSE_ACCEPT, NULL);

    filter = gtk_file_filter_new();

    gtk_file_filter_add_pattern(filter, "*.gif");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    gtk_widget_show_all(dialog);

    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));

    if (resp == GTK_RESPONSE_ACCEPT){
        std::string fname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        gif_animation.unref_gif();

        gif_animation.open_file(fname);

        gtk_label_set_text(GTK_LABEL(speed_indicator_msg), "100 %");
    }

    gif_animation.set_place(gif_place); 

    gif_animation.smart_resize();

    gtk_widget_destroy(dialog);

    gtk_window_resize(GTK_WINDOW(main_window), 1, 1);

    pp_btn_icon();

    g_object_unref(dialog);
}

//

void set_icons(){
    if(get_param(THEME) == "system") {

    }
    else if(get_param(THEME) == "marshmallow") {
        gtk_button_set_image(GTK_BUTTON(option_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_settings.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_play.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_re_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_reset.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_down_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_minus.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_up_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_plus.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(prev_image_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_prev_frame.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(next_image_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_next_frame.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(exit_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_exit.png", NULL), 30, 30, GDK_INTERP_HYPER)));
    }
    else {
        gtk_button_set_image(GTK_BUTTON(option_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_settings.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(exit_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_exit.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_play.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_re_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_reset.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_down_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_minus.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(speed_up_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_plus.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(prev_image_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_prev_frame.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        gtk_button_set_image(GTK_BUTTON(next_image_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_next_frame.png", NULL), 30, 30, GDK_INTERP_HYPER)));
    }
}

//

void size_changed(){

}

//

void reset_speed(){
    gtk_label_set_text(GTK_LABEL(speed_indicator_msg), "100 %");

    if(!gif_animation.reset_speed()) return;

    pp_btn_icon();
}

//

void decrement_speed(){
    if(!gif_animation.speed_dec()) return;

    gtk_label_set_text(GTK_LABEL(speed_indicator_msg), std::string(std::to_string(gif_animation.get_speed_in_procents()) + " %").c_str());

    pp_btn_icon();
}

//

void increment_speed(){
    if(!gif_animation.speed_inc()) return;

    gtk_label_set_text(GTK_LABEL(speed_indicator_msg), std::string(std::to_string(gif_animation.get_speed_in_procents()) + " %").c_str());

    pp_btn_icon();
}

//

void change_status(){
    if(gif_animation.play_pause() == false) return;

    pp_btn_icon();
}

//

void frame_plus(){
    gif_animation.next_frame();

    pp_btn_icon();
}

//

void frame_minus(){
    gif_animation.previous_frame();

    pp_btn_icon();
}


void pp_btn_icon(){
    if(gif_animation.get_play() == true){
        if(get_param(THEME) == "system") gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/s_play.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        else if(get_param(THEME) == "marshmallow") gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_play.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        else gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_play.png", NULL), 30, 30, GDK_INTERP_HYPER)));

    }
    else{
        if(get_param(THEME) == "system") gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/s_pause.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        else if(get_param(THEME) == "marshmallow") gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/m_pause.png", NULL), 30, 30, GDK_INTERP_HYPER)));
        else gtk_button_set_image(GTK_BUTTON(play_btn), gtk_image_new_from_pixbuf(gdk_pixbuf_scale_simple(gdk_pixbuf_new_from_file("image/o_pause.png", NULL), 30, 30, GDK_INTERP_HYPER)));
    }
}

//

void setting_programm(){
    open_setting_win();
}
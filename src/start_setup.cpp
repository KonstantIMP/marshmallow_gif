#include "../include/start_setup.hpp"
#include "../include/config.hpp"

#define START_SETUP_FORM "form/start_setup.glade"

#define START_SYS_CSS "style/start_setup_system.css"
#define START_MARSH_CSS "style/start_setup_marshmallow.css"
#define START_OR_CSS "style/start_setup_oranje.css"

#include <gtk/gtk.h>
#include <locale>

std::string theme_s;

// -------------------- Прототипы функций --------------------

static GtkWidget * create_window();

void connect_signals();

void connect_css();

void set_sys_css();
void set_marsh_css();
void set_or_css();

void set_lang_by_system();

void set_ru();
void set_en();

void change_lang();

void end_setup();

// -------------------- Объекты окна --------------------

GtkWidget * window;

GtkWidget * lang_btn;
GtkWidget * sys_btn;
GtkWidget * marsh_btn;
GtkWidget * or_btn;
GtkWidget * ok_btn;

GtkWidget * hello_msg;
GtkWidget * thank_msg;
GtkWidget * theme_msg;
GtkWidget * sys_msg;
GtkWidget * marsh_msg;
GtkWidget * or_msg;

GtkWidget * up_sep;
GtkWidget * down_sep;

GtkCssProvider * setup_css;

GtkWidget * en;
GtkWidget * ru;

// -------------------- Функция обработчик окна настроек ----------------------

void start_setup(){
    theme_s = "sys";

    window = create_window();

    gtk_widget_show(window);

    gtk_main();

    g_object_unref(window);
}

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

    gtk_window_set_icon_from_file(GTK_WINDOW(setup_win), "image/start.png", NULL);
    gtk_window_set_title(GTK_WINDOW(setup_win), "Let`s go");

    if(!(setup_win)){
        g_critical("Unable to load window");

        exit(11);
    }

    lang_btn = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "lang_btn"));
    sys_btn = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "sys_btn"));
    marsh_btn = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "marsh_btn"));
    or_btn = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "or_btn"));
    ok_btn = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "ok_btn"));

    hello_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "hello_msg"));
    thank_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "thank_msg"));
    theme_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "theme_msg"));
    sys_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "sys_msg"));
    marsh_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "marsh_msg"));
    or_msg = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "or_msg"));

    up_sep = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "up_sep"));
    down_sep = GTK_WIDGET(gtk_builder_get_object(setup_win_builder, "down_sep"));

    connect_css();

    connect_signals();

    gtk_window_set_default_size(GTK_WINDOW(setup_win), -1, -1);
    gtk_window_set_resizable(GTK_WINDOW(setup_win), FALSE);

    gtk_label_set_max_width_chars (GTK_LABEL(thank_msg), 50);

    gtk_widget_set_name(GTK_WIDGET(setup_win), "setup_win");

    g_signal_connect(G_OBJECT(setup_win), "destroy", G_CALLBACK(end_setup), NULL);

    set_lang_by_system();

    g_object_unref(setup_win_builder);

    gtk_container_set_border_width(GTK_CONTAINER(setup_win), 7);

    return setup_win;
}

// -------------------- Подключение CSS --------------------

void connect_css(){
    setup_css = gtk_css_provider_new();

    set_sys_css();

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(setup_css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_set_name(GTK_WIDGET(lang_btn), "lang_btn");
    gtk_widget_set_name(GTK_WIDGET(sys_btn), "sys_btn");
    gtk_widget_set_name(GTK_WIDGET(marsh_btn), "marsh_btn");
    gtk_widget_set_name(GTK_WIDGET(or_btn), "or_btn");
    gtk_widget_set_name(GTK_WIDGET(ok_btn), "ok_btn");

    gtk_widget_set_name(GTK_WIDGET(hello_msg), "hello_msg");
    gtk_widget_set_name(GTK_WIDGET(thank_msg), "thank_msg");
    gtk_widget_set_name(GTK_WIDGET(theme_msg), "theme_msg");
    gtk_widget_set_name(GTK_WIDGET(sys_msg), "sys_msg");
    gtk_widget_set_name(GTK_WIDGET(marsh_msg), "marsh_msg");
    gtk_widget_set_name(GTK_WIDGET(or_msg), "or_msg");

    gtk_widget_set_name(GTK_WIDGET(up_sep), "up_sep");
    gtk_widget_set_name(GTK_WIDGET(down_sep), "down_sep");
}

// -------------------- Системныя тема --------------------

void set_sys_css(){
    gtk_css_provider_load_from_path(setup_css, START_SYS_CSS, NULL);

    theme_s = "sys";
}

// -------------------- Розовая тема --------------------

void set_marsh_css(){
    gtk_css_provider_load_from_path(setup_css, START_MARSH_CSS, NULL);

    theme_s = "marsh";
}

// -------------------- Оранжевая тема --------------------

void set_or_css(){
    gtk_css_provider_load_from_path(setup_css, START_OR_CSS, NULL);

    theme_s = "or";
}

// -------------------- Установка языка ----------------------

void set_lang_by_system(){
    std::string lang = std::locale("").name();

    en = gtk_image_new_from_file("image/en.png");

    ru = gtk_image_new_from_file("image/ru.png");

    if(lang == "ru_RU.UTF-8") set_ru();
    else set_en();
}

// -------------------- Русский язык --------------------

void set_ru(){
    gtk_button_set_image(GTK_BUTTON(lang_btn), NULL);

    g_object_unref(en);
    en = gtk_image_new_from_file("image/en.png");

    gtk_button_set_image(GTK_BUTTON(lang_btn), en);
    gtk_button_set_label(GTK_BUTTON(lang_btn), "EN");
    gtk_button_set_image_position(GTK_BUTTON(lang_btn), GTK_POS_LEFT);

    gtk_button_set_label(GTK_BUTTON(sys_btn), "Классический");

    gtk_button_set_label(GTK_BUTTON(marsh_btn), "Фирменный");

    gtk_button_set_label(GTK_BUTTON(or_btn), "Мандарин");

    gtk_button_set_label(GTK_BUTTON(ok_btn), "Ок");

    gtk_label_set_text(GTK_LABEL(hello_msg), "Привет!");
    gtk_label_set_justify(GTK_LABEL(hello_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(thank_msg), "Спасибо за выбор нашего програмного обеспечения!\nПриятного использования!");
    gtk_label_set_justify(GTK_LABEL(thank_msg), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap (GTK_LABEL(thank_msg), TRUE);

    gtk_label_set_text(GTK_LABEL(theme_msg), "Выберите оформление :");
    gtk_label_set_justify(GTK_LABEL(theme_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(sys_msg), "Системный :");
    gtk_label_set_justify(GTK_LABEL(sys_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(marsh_msg), "Зефирный :");
    gtk_label_set_justify(GTK_LABEL(marsh_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(or_msg), "Оранжевый :");
    gtk_label_set_justify(GTK_LABEL(or_msg), GTK_JUSTIFY_CENTER);
}

// -------------------- Английский язык --------------------

void set_en(){
    gtk_button_set_image(GTK_BUTTON(lang_btn), NULL);

    g_object_unref(ru);
    ru = gtk_image_new_from_file("image/ru.png");

    gtk_button_set_image(GTK_BUTTON(lang_btn), ru);
    gtk_button_set_label(GTK_BUTTON(lang_btn), "RU");
    gtk_button_set_image_position(GTK_BUTTON(lang_btn), GTK_POS_LEFT);

    gtk_button_set_label(GTK_BUTTON(sys_btn), "Classic");

    gtk_button_set_label(GTK_BUTTON(marsh_btn), "Branded");

    gtk_button_set_label(GTK_BUTTON(or_btn), "Oranje");

    gtk_button_set_label(GTK_BUTTON(ok_btn), "Ok");

    gtk_label_set_text(GTK_LABEL(hello_msg), "Hi!");
    gtk_label_set_justify(GTK_LABEL(hello_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(thank_msg), "Thanks for using this programm!\nEnjoy using!");
    gtk_label_set_justify(GTK_LABEL(thank_msg), GTK_JUSTIFY_CENTER);
    gtk_label_set_line_wrap (GTK_LABEL(thank_msg), TRUE);

    gtk_label_set_text(GTK_LABEL(theme_msg), "Choose style :");
    gtk_label_set_justify(GTK_LABEL(theme_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(sys_msg), "System :");
    gtk_label_set_justify(GTK_LABEL(sys_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(marsh_msg), "Marshmallow :");
    gtk_label_set_justify(GTK_LABEL(marsh_msg), GTK_JUSTIFY_CENTER);

    gtk_label_set_text(GTK_LABEL(or_msg), "Oranje :");
    gtk_label_set_justify(GTK_LABEL(or_msg), GTK_JUSTIFY_CENTER);
}

// -------------------- Смена языка --------------------

void change_lang(){
    char *lang = {(char*)gtk_button_get_label(GTK_BUTTON(lang_btn))};

    if(lang[0] == 'E' && lang[1] == 'N') set_en();
    else set_ru();
}

// -------------------- Подключение сигналов ----------------------

void connect_signals(){
    g_signal_connect(G_OBJECT(lang_btn), "clicked", G_CALLBACK(change_lang), NULL);
    g_signal_connect(G_OBJECT(sys_btn), "clicked", G_CALLBACK(set_sys_css), NULL);
    g_signal_connect(G_OBJECT(marsh_btn), "clicked", G_CALLBACK(set_marsh_css), NULL);
    g_signal_connect(G_OBJECT(or_btn), "clicked", G_CALLBACK(set_or_css), NULL);
    g_signal_connect(G_OBJECT(ok_btn), "clicked", G_CALLBACK(end_setup), NULL);
}

// -------------------- Окончание первичной настройки ----------------------

void end_setup(){
    char *lang = {(char*)gtk_button_get_label(GTK_BUTTON(lang_btn))};

    std::string language;

    if(lang[0] == 'E' && lang[1] == 'N') language = "ru";
    else language = "en";

    create_cfg(theme_s, language, STANDART, STANDART, STANDART, STANDART);

    gtk_main_quit();
}
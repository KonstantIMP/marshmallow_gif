#include "../include/gtk_setting.hpp"
#include "../include/config.hpp"

#include <gtk/gtk.h>

#define OPTION_WIN_FROM "form/setting_win.glade"

#define OPT_SYSTEM_THEME "style/opt_system.css"
#define OPT_MARSH_THEME "style/opt_marshmallow.css"
#define OPT_OR_THEME "style/opt_oranje.css"

//

GtkWidget * setting_win;

GtkWidget * setting_msg;
GtkWidget * theme_c_msg;
GtkWidget * lang_msg;
GtkWidget * lot_msg;
GtkWidget * update_msg;

GtkWidget * theme_combo;
GtkWidget * lang_combo;
GtkWidget * lot_combo;
GtkWidget * update_combo;

GtkWidget * cancel_btn;
GtkWidget * ok_c_btn;

GtkCssProvider * option_css;

//

static GtkWidget * create_option_win();

void connect_option_css();

void set_text_lang();

void rewrite_config();

//

void open_setting_win(){
    setting_win = create_option_win();

    gtk_widget_show_all(setting_win);

    gtk_main();

    g_object_unref(setting_win);
}    

//

static GtkWidget * create_option_win(){
    GtkWidget * opt_win;

    GtkBuilder * opt_win_builder;

    GError * err_msg = NULL;

    opt_win_builder = gtk_builder_new();

    if(!(gtk_builder_add_from_file(opt_win_builder, OPTION_WIN_FROM, &err_msg))){
            g_critical("Unable to load form file %s", err_msg->message);

            g_error_free(err_msg);

            exit(30);
    }

    gtk_builder_connect_signals(opt_win_builder, NULL);

    opt_win = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "setting_win"));

    if(!(opt_win)){
            g_critical("Unable to load window");

            exit(31);
    }

    if(get_param(THEME) == "system") gtk_window_set_icon_from_file(GTK_WINDOW(opt_win), "image/s_settings.png", NULL);
    else if(get_param(THEME) == "marshmallow") gtk_window_set_icon_from_file(GTK_WINDOW(opt_win), "image/m_settings.png", NULL);
    else gtk_window_set_icon_from_file(GTK_WINDOW(opt_win), "image/o_settings.png", NULL);

    if(get_param(LANG) == "ru") gtk_window_set_title(GTK_WINDOW(opt_win), "Настройки");
    else gtk_window_set_title(GTK_WINDOW(opt_win), "Settings");

    setting_msg = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "setting_msg"));
    theme_c_msg = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "theme_msg"));
    lang_msg = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "lang_msg"));
    lot_msg = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "lot_msg"));
    update_msg = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "update_msg"));

    theme_combo = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "theme_combo"));
    lang_combo = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "lang_combo"));
    lot_combo = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "lot_combo"));
    update_combo = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "update_combo"));

    cancel_btn = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "cancel_btn"));
    ok_c_btn = GTK_WIDGET(gtk_builder_get_object(opt_win_builder, "ok_btn"));

    connect_option_css();

    gtk_widget_set_name(GTK_WIDGET(opt_win), "setting_win");

    set_text_lang();

    gtk_window_set_default_size(GTK_WINDOW(opt_win), 500, 150);

    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(gtk_window_close), GTK_WINDOW(opt_win));
    g_signal_connect(G_OBJECT(ok_c_btn), "clicked", G_CALLBACK(rewrite_config), NULL);

    g_signal_connect(G_OBJECT(opt_win), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(option_css);

    if(err_msg != NULL) g_error_free(err_msg);

    return opt_win;
}

//

void connect_option_css(){
    option_css = gtk_css_provider_new();

    if(get_param(THEME) == "system") gtk_css_provider_load_from_path(option_css, OPT_SYSTEM_THEME, NULL);
    else if(get_param(THEME) == "marshmallow") gtk_css_provider_load_from_path(option_css, OPT_MARSH_THEME, NULL);
    else gtk_css_provider_load_from_path(option_css, OPT_OR_THEME, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(option_css), GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_set_name(GTK_WIDGET(setting_msg), "setting_msg");
    gtk_widget_set_name(GTK_WIDGET(theme_c_msg), "theme_msg");
    gtk_widget_set_name(GTK_WIDGET(lang_msg), "lang_msg");
    gtk_widget_set_name(GTK_WIDGET(lot_msg), "lot_msg");
    gtk_widget_set_name(GTK_WIDGET(update_msg), "update_msg");

    gtk_widget_set_name(GTK_WIDGET(theme_combo), "theme_combo");
    gtk_widget_set_name(GTK_WIDGET(lang_combo), "lang_combo");
    gtk_widget_set_name(GTK_WIDGET(lot_combo), "lot_combo");
    gtk_widget_set_name(GTK_WIDGET(update_combo), "update_combo");

    gtk_widget_set_name(GTK_WIDGET(ok_c_btn), "ok_btn");
    gtk_widget_set_name(GTK_WIDGET(cancel_btn), "cancel_btn");
}

//

void set_text_lang(){
    if(get_param(LANG) == "ru") {
        gtk_label_set_text(GTK_LABEL(setting_msg), "Настройки");
        gtk_label_set_xalign(GTK_LABEL(setting_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(theme_c_msg), "Тема приложения :");
        gtk_label_set_xalign(GTK_LABEL(theme_c_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(lang_msg), "Язык приложения :");
        gtk_label_set_xalign(GTK_LABEL(lang_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(lot_msg), "Несколько файлов :");
        gtk_label_set_xalign(GTK_LABEL(lot_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(update_msg), "Автообновление :");
        gtk_label_set_xalign(GTK_LABEL(update_msg), 0.10);

        gtk_button_set_label(GTK_BUTTON(cancel_btn), "Отмена");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "0", "Системный");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "1", "Зефирный");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "2", "Оранжевый");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lang_combo), "0", "Русский");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lang_combo), "1", "English");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lot_combo), "0", "Открывать последний");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lot_combo), "1", "Открывать несколько экземпляров");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "0", "Отключено");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "1", "Спрашивать");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "2", "Автоматически");
    }
    else {
        gtk_label_set_text(GTK_LABEL(setting_msg), "Options");
        gtk_label_set_xalign(GTK_LABEL(setting_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(theme_c_msg), "App theme :");
        gtk_label_set_xalign(GTK_LABEL(theme_c_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(lang_msg), "App language :");
        gtk_label_set_xalign(GTK_LABEL(lang_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(lot_msg), "A lot of files :");
        gtk_label_set_xalign(GTK_LABEL(lot_msg), 0.1);

        gtk_label_set_text(GTK_LABEL(update_msg), "Autoupdate :");
        gtk_label_set_xalign(GTK_LABEL(update_msg), 0.10);

        gtk_button_set_label(GTK_BUTTON(cancel_btn), "Cancel");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "0", "System");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "1", "Marshmallow");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(theme_combo), "2", "Oranje");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lang_combo), "0", "Русский");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lang_combo), "1", "English");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lot_combo), "0", "Open the last");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(lot_combo), "1", "Open all");

        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "0", "Disable");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "1", "Asking");
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(update_combo), "2", "Automatically");
    }

    if(get_param(THEME) == "system") gtk_combo_box_set_active(GTK_COMBO_BOX(theme_combo), 0);
    else if(get_param(THEME) == "marshmallow") gtk_combo_box_set_active(GTK_COMBO_BOX(theme_combo), 1);
    else gtk_combo_box_set_active(GTK_COMBO_BOX(theme_combo), 2);

    if(get_param(LANG) == "ru") gtk_combo_box_set_active(GTK_COMBO_BOX(lang_combo), 0);
    else gtk_combo_box_set_active(GTK_COMBO_BOX(lang_combo), 1);

    if(get_param(LOTS) == "last") gtk_combo_box_set_active(GTK_COMBO_BOX(lot_combo), 0);
    else gtk_combo_box_set_active(GTK_COMBO_BOX(lot_combo), 1);

    if(get_param(UPDATE) == "dis") gtk_combo_box_set_active(GTK_COMBO_BOX(update_combo), 0);
    else if(get_param(UPDATE) == "ask") gtk_combo_box_set_active(GTK_COMBO_BOX(update_combo), 1);
    else gtk_combo_box_set_active(GTK_COMBO_BOX(update_combo), 2);
}

//

void rewrite_config(){
    std::string theme_p;
    std::string lang_p;
    std::string lot_p;
    std::string update_p;

    switch(gtk_combo_box_get_active(GTK_COMBO_BOX(theme_combo))){
        case 0: theme_p = "sys"; break;
        case 1: theme_p = "marsh"; break;
        case 2: theme_p = "oranje"; break;
    }

    if(gtk_combo_box_get_active(GTK_COMBO_BOX(lang_combo)) == 0) lang_p = "ru";
    else lang_p = "en";

    if(gtk_combo_box_get_active(GTK_COMBO_BOX(lot_combo)) == 0) lot_p = "last";
    else lot_p = "all";

    switch(gtk_combo_box_get_active(GTK_COMBO_BOX(update_combo))){
        case 0: update_p = "dis"; break;
        case 1: update_p = "ask"; break;
        case 2: update_p = "auto"; break;
    }

    delete_cfg();

    create_cfg("gtk", theme_p, lang_p, STANDART, STANDART, lot_p, update_p);

    GtkWidget * warning_dialog;

    if(get_param(LANG) == "ru") {
        warning_dialog = gtk_message_dialog_new(GTK_WINDOW(setting_win), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "Изменения вступят в силу после перезапуска");
    }
    else {
        warning_dialog = gtk_message_dialog_new(GTK_WINDOW(setting_win), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "Changes will take effect after restart");
    }

    gtk_widget_show_all(GTK_WIDGET(warning_dialog));

    gtk_dialog_run(GTK_DIALOG(warning_dialog));

    gtk_widget_destroy(warning_dialog);

    gtk_window_close(GTK_WINDOW(setting_win));

    g_object_unref(warning_dialog);
}

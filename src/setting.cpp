#include "../include/setting.hpp"
#include "../include//config.hpp"

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

//

void open_setting_win(){
    setting_win = create_option_win();

    gtk_widget_show_all(setting_win);

    gtk_main();
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

            exit(21);
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

    return opt_win;
}

//

void connect_option_css(){
    option_css = gtk_css_provider_new();

    if(get_param(THEME) == "system") gtk_css_provider_load_from_path(option_css, OPT_SYSTEM_THEME, NULL);
    else if(get_param(THEME) == "marshmallow") gtk_css_provider_load_from_path(option_css, OPT_MARSH_THEME, NULL);
    else gtk_css_provider_load_from_path(option_css, OPT_OR_THEME, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(option_css), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
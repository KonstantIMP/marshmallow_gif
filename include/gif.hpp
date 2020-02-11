#ifndef GIF_HPP
#define GIF_HPP

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <string>

class gif_viewer
{
public:
    gif_viewer();

    ~gif_viewer();
  
    void open_file(std::string);

    void set_place(GtkWidget *);

    void play_pause();

    void speed_inc();

    void speed_dec();

    void reset_speed();

    void next_frame();

    void previous_frame();

    void unref_gif();

private:
    std::string file_name;

    GtkWidget * frame_place;

    GdkPixbufAnimation * gif_animation;

    int speed;

    bool play_status;
};

#endif
#ifndef GIF_HPP
#define GIF_HPP

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <glib.h>
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

    void smart_resize();

    void reset();

private:
    std::string file_name;

    GtkWidget * frame_place;

    GdkPixbufSimpleAnim * simple_gif_animation;

    float default_speed;

    int speed;

    bool play_status;

    int max_h;
    int max_w;

    int  gif_animation_h, gif_animation_w;

    void get_gif_size();

    int get_number_of_frames();
};

#endif
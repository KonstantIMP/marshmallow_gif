#include "../include/gif.hpp"

#include <fstream>
#include <Magick++.h> 
#include <iostream>
#include <sstream>

gif_viewer::gif_viewer(){
    play_status = false;

    file_name = "";

    gtk_init(NULL, NULL);

    max_w = gdk_screen_get_width(gdk_screen_get_default());
    max_h = gdk_screen_get_height(gdk_screen_get_default());

    speed_in_procents = 100;

    frame_place = NULL;
    gif_animation = NULL;
}

gif_viewer::~gif_viewer(){

}

void gif_viewer::open_file(std::string name_of_gif){
    file_name = name_of_gif;

    gif_animation = conversion_gif();

    gtk_widget_set_size_request(GTK_WIDGET(frame_place), gif_animation_w, gif_animation_h);
}

void gif_viewer::set_place(GtkWidget * place_for_animation){
    frame_place = place_for_animation;

    gtk_image_set_from_animation(GTK_IMAGE(place_for_animation), gif_animation);
}

void gif_viewer::play_pause(){

}

bool gif_viewer::speed_inc(){
    if(file_name == "") return false;
    if(speed_in_procents <= 995) speed_in_procents += 5;
    else speed_in_procents = 5;
    open_file(file_name);
    set_place(frame_place);
    return true;    
}

bool gif_viewer::speed_dec(){
    if(file_name == "") return false;
    if(speed_in_procents > 5) speed_in_procents -= 5;
    else speed_in_procents = 1000;
    open_file(file_name);
    set_place(frame_place);
    return true;
}

bool gif_viewer::reset_speed(){
    speed_in_procents = 100;
    if(file_name == "") return false;
    open_file(file_name);
    set_place(frame_place);
    return true;
}

void gif_viewer::previous_frame(){

}

void gif_viewer::next_frame(){

}

void gif_viewer::unref_gif(){

}

void gif_viewer::smart_resize(){
    if(file_name == "")return;

    int gif_place_h;
    int gif_place_w;

    get_gif_size();

    GtkAllocation gif_place_alloc;

    gtk_widget_get_allocation(GTK_WIDGET(frame_place), &gif_place_alloc);

    gif_place_w = gif_place_alloc.width;
    gif_place_h = gif_place_alloc.height;

    int tmp_w, tmp_h;

    
}

void gif_viewer::get_gif_size(){
    if(file_name == "")return;

    std::ifstream gif_file;
    gif_file.open(file_name, std::ios::binary);

    unsigned char byte;

    for(int i{0}; i< 10; i++){
        gif_file>> byte;
        
        if(i == 6) gif_animation_w = (int)byte;
        if(i == 7) gif_animation_w += (int)byte*256;

        if(i == 8) gif_animation_h = (int)byte;
        if(i == 9) gif_animation_h += (int)byte*256;
    }

    gif_file.close();
}

int gif_viewer::get_number_of_frames(){
    if(file_name == "")return 0;

    Magick::Image temp;
    int total_frames = 0;

    std::string file_out = file_name + "[-1]";

    temp.ping(file_out.c_str());
    total_frames = temp.scene() + 1;

    return total_frames;
}

GdkPixbufAnimation * gif_viewer::conversion_gif(){
    if(file_name == "")return NULL;

    get_gif_size();

    smart_resize();

    GTimeVal time_pointer;

    GdkPixbuf * frame;

    GdkPixbufAnimation * tmp_gif;

    GdkPixbufSimpleAnim * simple_gif_animation;

    GdkPixbufAnimationIter * frame_pointer; 

    g_get_current_time(&time_pointer);

    tmp_gif = gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL);

    frame_pointer = gdk_pixbuf_animation_get_iter(tmp_gif, &time_pointer);

    simple_gif_animation = gdk_pixbuf_simple_anim_new(gif_animation_w, gif_animation_h, 1000 / ((double)gdk_pixbuf_animation_iter_get_delay_time(frame_pointer) * 100 / (double)speed_in_procents)); //((double)(1000 / gdk_pixbuf_animation_iter_get_delay_time(frame_pointer)) / (double)((double)speed_in_procents / 100)));

    gdk_pixbuf_simple_anim_set_loop(simple_gif_animation, TRUE);

    for(int i{0}; i < get_number_of_frames(); i++){
        frame = gdk_pixbuf_scale_simple(gdk_pixbuf_animation_iter_get_pixbuf(frame_pointer), gif_animation_w, gif_animation_h, GDK_INTERP_NEAREST);

        if(frame == NULL) break;

        g_time_val_add(&time_pointer, gdk_pixbuf_animation_iter_get_delay_time(frame_pointer) * 1000);
    
        gdk_pixbuf_simple_anim_add_frame(simple_gif_animation, frame);

        if(gdk_pixbuf_animation_iter_advance(frame_pointer, &time_pointer) == FALSE) break;
    }

    return (GdkPixbufAnimation *)simple_gif_animation;
}

int gif_viewer::get_speed_in_procents(){
    return speed_in_procents;
}
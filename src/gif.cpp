#include "../include/gif.hpp"

#include <Magick++.h> 
#include <iostream>
#include <sstream>

gif_viewer::gif_viewer(){
    play_status = false;

    file_name = "";

    num_frame = 0;

    speed_in_procents = 100;

    frame_place = NULL;
}

gif_viewer::~gif_viewer(){

}

void gif_viewer::open_file(std::string name_of_gif){
    if(name_of_gif != file_name) speed_in_procents = 100;

    file_name = name_of_gif;

    play_status = true;
}

void gif_viewer::set_place(GtkWidget * place_for_animation){
    frame_place = place_for_animation;

    if(file_name == "") return;

    gtk_image_set_from_animation(GTK_IMAGE(place_for_animation), conversion_gif());
}

bool gif_viewer::play_pause(){
    if(file_name == "") return false;

    get_gif_size();

    smart_resize();

    if(play_status == true){
        gtk_image_set_from_pixbuf(GTK_IMAGE(frame_place),gdk_pixbuf_animation_iter_get_pixbuf(gdk_pixbuf_animation_get_iter(gtk_image_get_animation(GTK_IMAGE(frame_place)), NULL)));

        num_frame = 1;

        play_status = false;
    }
    else{
        open_file(file_name);

        set_place(frame_place);

        play_status = true;
    }

    return true;
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
    num_frame = 0;
    return true;
}

void gif_viewer::previous_frame(){
    if(file_name == "") return;

    num_frame--;

    if(num_frame <= 0){
        num_frame = get_number_of_frames();
    }
    
    GTimeVal time_pointer;

    GdkPixbufAnimationIter * frame_pointer; 

    time_pointer.tv_sec = g_get_real_time() / 1000;
    time_pointer.tv_usec = g_get_real_time() % 1000;

    frame_pointer = gdk_pixbuf_animation_get_iter(gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL), &time_pointer);

    for(int i{0}; i < num_frame; i++){
        g_time_val_add(&time_pointer, gdk_pixbuf_animation_iter_get_delay_time(frame_pointer) * 1000);

        gdk_pixbuf_animation_iter_advance(frame_pointer, &time_pointer);
    }

    play_status = false;

    smart_resize();

    gtk_image_set_from_pixbuf(GTK_IMAGE(frame_place), gdk_pixbuf_scale_simple(gdk_pixbuf_animation_iter_get_pixbuf(frame_pointer), gif_animation_w, gif_animation_h, GDK_INTERP_NEAREST));

    g_object_unref(frame_pointer);
}

void gif_viewer::next_frame(){
    if(file_name == "") return;

    if(num_frame == 0){
        play_status = true;

        play_pause();

        num_frame++;
    }
    else{
        if(num_frame < get_number_of_frames()){
            num_frame++;

            GTimeVal time_pointer;

            GdkPixbufAnimationIter * frame_pointer; 

            time_pointer.tv_sec = g_get_real_time() / 1000;
            time_pointer.tv_usec = g_get_real_time() % 1000;

            frame_pointer = gdk_pixbuf_animation_get_iter(gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL), &time_pointer);

            for(int i{0}; i < num_frame; i++){
                g_time_val_add(&time_pointer, gdk_pixbuf_animation_iter_get_delay_time(frame_pointer) * 1000);

                gdk_pixbuf_animation_iter_advance(frame_pointer, &time_pointer);
            }

            play_status = false;

            smart_resize();

            gtk_image_set_from_pixbuf(GTK_IMAGE(frame_place), gdk_pixbuf_scale_simple(gdk_pixbuf_animation_iter_get_pixbuf(frame_pointer), gif_animation_w, gif_animation_h, GDK_INTERP_NEAREST));
        
            g_object_unref(frame_pointer);
        }
        else{
            gtk_image_set_from_pixbuf(GTK_IMAGE(frame_place), gdk_pixbuf_scale_simple(gdk_pixbuf_animation_iter_get_pixbuf(gdk_pixbuf_animation_get_iter(gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL), NULL)), gif_animation_w, gif_animation_h, GDK_INTERP_NEAREST));

            num_frame = 1;

            play_status = false;
        }
    }
}

void gif_viewer::unref_gif(){
    g_object_unref(simple_gif_animation);
}

void gif_viewer::smart_resize(){
    if(file_name == "")return;

    int gif_place_h;
    int gif_place_w;

    get_gif_size();

    gtk_widget_get_size_request(GTK_WIDGET(frame_place), &gif_place_w, &gif_place_h);

    int tmp_w, tmp_h;

    if(gif_animation_w < gif_place_w && gif_animation_h < gif_place_w){
        if(gif_animation_w > gif_animation_h){
            tmp_w = gif_animation_w;

            gif_animation_w = gif_place_w;

            gif_animation_h = (gif_animation_w * gif_animation_h) / tmp_w;
        }
        else{
            tmp_h = gif_animation_h;

            gif_animation_h = gif_place_h;

            gif_animation_w = (gif_animation_h * gif_animation_w) / tmp_h;
        }
    }

    if(gif_animation_w > gif_place_w || gif_animation_h > gif_place_h){
        if(gif_animation_h > gif_place_h){
            tmp_h = gif_animation_h;

            gif_animation_h = gif_place_h;

            gif_animation_w = (gif_animation_h * gif_animation_w) / tmp_h;
        }
        if(gif_animation_w > gif_place_w){
            tmp_w = gif_animation_w;

            gif_animation_w = gif_place_w;

            gif_animation_h = (gif_animation_w * gif_animation_h) / tmp_w;
        }
    }
}

void gif_viewer::get_gif_size(){
    gif_animation_w = gdk_pixbuf_animation_get_width(gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL));
    gif_animation_h = gdk_pixbuf_animation_get_height(gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL));
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

    unref_gif();

    GTimeVal time_pointer;

    GdkPixbuf * frame;

    GdkPixbufAnimation * tmp_gif;

    GdkPixbufAnimationIter * frame_pointer; 

    time_pointer.tv_sec = g_get_real_time() / 1000;
    time_pointer.tv_usec = g_get_real_time() % 1000;

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

    g_object_unref(frame);
    g_object_unref(tmp_gif);
    g_object_unref(frame_pointer);

    return (GdkPixbufAnimation *)simple_gif_animation;
}

int gif_viewer::get_speed_in_procents(){
    return speed_in_procents;
}

bool gif_viewer::get_play(){
    return play_status;
}

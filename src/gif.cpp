#include "../include/gif.hpp"

#include <fstream>

#include <iostream>
#include <sstream>

#if defined(linux) || defined(__linux)
    #include <X11/Xlib.h>
#elif defined(_WIN32) || defined (_WIN64)

#else

#endif

gif_viewer::gif_viewer(){
    speed = 100;

    play_status = false;

    file_name = "";

    #if defined(linux) || defined(__linux)
        Display* disp = XOpenDisplay(NULL);

        Screen*  srcn = DefaultScreenOfDisplay(disp);

        max_h = srcn->height; max_w = srcn->width;

        delete srcn;
    #elif defined(_WIN32) || defined (_WIN64)

    #else

    #endif

    frame_place = NULL;
    simple_gif_animation = NULL;
}

gif_viewer::~gif_viewer(){

}

void gif_viewer::open_file(std::string name_of_gif){
    file_name = name_of_gif;
    
    get_gif_size();

    smart_resize();

    GTimeVal what;

    GdkPixbuf * frame;

    GdkPixbufAnimation * tmp_gif;

    GdkPixbufAnimationIter * gif_iter;

    g_get_current_time(&what);

    tmp_gif = gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL);

    gif_iter = gdk_pixbuf_animation_get_iter(tmp_gif, &what);

    if(simple_gif_animation != NULL) g_object_unref(simple_gif_animation);

    simple_gif_animation = gdk_pixbuf_simple_anim_new(gif_animation_w, gif_animation_h, 1000 / gdk_pixbuf_animation_iter_get_delay_time(gif_iter));

    gdk_pixbuf_simple_anim_set_loop(simple_gif_animation, TRUE);

    get_number_of_frames();

    for(int i{0}; i < 100; i++){
        frame = gdk_pixbuf_scale_simple(gdk_pixbuf_animation_iter_get_pixbuf(gif_iter), gif_animation_w, gif_animation_h, GDK_INTERP_NEAREST);

        if(frame == NULL) break;

        g_time_val_add(&what, gdk_pixbuf_animation_iter_get_delay_time(gif_iter) * 1000);

        gdk_pixbuf_simple_anim_add_frame(simple_gif_animation, frame);

        if(gdk_pixbuf_animation_iter_advance(gif_iter,&what) == FALSE) break;
    }

    gtk_widget_set_size_request(GTK_WIDGET(frame_place), gif_animation_w, gif_animation_h);
}

void gif_viewer::set_place(GtkWidget * place_for_animation){
    frame_place = place_for_animation;

    gtk_image_set_from_animation(GTK_IMAGE(place_for_animation), (GdkPixbufAnimation *)simple_gif_animation);
}

void gif_viewer::play_pause(){

}

void gif_viewer::speed_inc(){

}

void gif_viewer::speed_dec(){

}

void gif_viewer::reset_speed(){

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

    if(gif_animation_w < (gif_place_w - 5) && gif_animation_h < (gif_place_h - 5)){
        if(gif_animation_w > gif_animation_h){
            tmp_w = gif_animation_w;

            gif_animation_w = gif_place_w - 5;

            gif_animation_h = (gif_animation_h * gif_animation_w) / tmp_w;
        }
        else{
            tmp_h = gif_animation_h;

            gif_animation_h = gif_place_h - 5;

            gif_animation_w = (gif_animation_w * gif_animation_h) / tmp_h;
        }
    }
    else if(gif_animation_w > (max_w - 50) || gif_animation_h > (max_h - 100)){

    }
    else{

    }
}

void gif_viewer::get_gif_size(){
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
    std::ifstream gif_file;
    gif_file.open(file_name, std::ios::binary);

    unsigned char byte;

    int number = 0;

    while(gif_file.peek() != EOF){
        gif_file >> byte;

        if(byte == 0x2c){
            gif_file >> byte;
            if(byte == 0xf9) number++;
        }
    }

    gif_file.close();

    return number;
}

void gif_viewer::reset(){
    if(file_name == "") return;

    open_file(file_name);
}
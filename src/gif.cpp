#include "../include/gif.hpp"

gif_viewer::gif_viewer(){
    speed = 100;

    play_status = false;

    file_name = "";
}

gif_viewer::~gif_viewer(){

}

void gif_viewer::open_file(std::string name_of_gif){
    file_name = name_of_gif;
    
    gif_animation = gdk_pixbuf_animation_new_from_file(file_name.c_str(), NULL);
}

void gif_viewer::set_place(GtkWidget * place_for_animation){
    frame_place = place_for_animation;

    gtk_image_set_from_animation(GTK_IMAGE(place_for_animation), gif_animation);
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
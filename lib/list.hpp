#ifndef LISTS_HPP
#define LISTS_HPP

#include <cstddef>

//-------------------- Определение класса --------------------

template<class object_type>
class list{
public:
    list();

    ~list();

    void add_to_end(object_type);
    void add_to_start(object_type);

    bool delete_first();
    bool delete_last();

    void clear_all();

    std::size_t get_size();

    object_type get_first();
    object_type get_last();
    object_type get_by_index(std::size_t);
private:
    struct node
    {
        object_type value;
        node * next_node;
    };

    std::size_t size;

    node * begin;
    node * end;
};

//-------------------- Реализация класса --------------------

template<class object_type>
list<object_type>::list(){
    size = 0;

    begin = NULL;
    end = NULL;
}

template<class object_type>
list<object_type>::~list(){
    clear_all();
}

template<class object_type>
void list<object_type>::add_to_end(object_type object){
    size++;

    if(begin == NULL){
        begin = new node;

        end = begin;
    }
    else{
        end->next_node = new node;
        
        end = end->next_node;
    }

    end->value = object;
    end->next_node = NULL;
}

template<class object_type>
void list<object_type>::add_to_start(object_type object){
    size++;

    if(begin = NULL){
        begin = new node;
        begin->next_node = NULL;
    }
    else{
        node *tmp = begin;

        begin = new node;

        begin->next_node = tmp;

        delete tmp;
    }

    begin->value = object;
}

template<class object_type>
bool list<object_type>::delete_first(){
    if(size == 0) return false;

    size--;

    if(size == 0){
        node *tmp = begin;

        begin = NULL;
        end = NULL;

        delete tmp;
    }
    else{
        node *tmp = begin;

        begin = begin->next_node;

        delete tmp;
    }

    return true;
}

template<class object_type>
bool list<object_type>::delete_last(){
    if(size == 0) return false;

    size--;

    if(size == 0){
        node *tmp = begin;

        begin = NULL;
        end = NULL;

        delete tmp;
    }
    else{
        node *tmp = end;

        end = begin;

        for(std::size_t i{0}; i < (size - 1); i++){
            end = end->next_node;
        }

        end->next_node = NULL;

        delete tmp;
    }

    return true;
}

template<class object_type>
void list<object_type>::clear_all(){
    while(delete_last());
}

template<class object_type>
std::size_t list<object_type>::get_size(){
    return size;
}

template<class object_type>
object_type list<object_type>::get_first(){
    if(size == 0) return NULL;
    return begin->value;
}

template<class object_type>
object_type list<object_type>::get_last(){
    if(size == 0) return NULL;
    return end->value;
}

template<class object_type>
object_type list<object_type>::get_by_index(std::size_t index){
    if(size == 0) return NULL;
    
    node *tmp = begin;

    for(std::size_t i{0}; i < index; i++) tmp = tmp->next_node;

    return tmp->value;
}

#endif
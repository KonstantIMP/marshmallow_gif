#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

//-------------------- Определение класса --------------------

template<class object_type>
class queue
{
public:
    queue();
    
    ~queue();

    std::size_t get_size();

    void enqueue(object_type);

    object_type dequeue();

    void clear_all();
    
private:
    struct node
    {
        object_type value;
        node *next_node;
    };

    std::size_t size;

    node *begin;
    node *end;
};

//-------------------- Реализация класса --------------------

template<class object_type>
queue<object_type>::queue(){
    size = 0;

    begin = NULL;
    end = NULL;
}

template<class object_type>
queue<object_type>::~queue(){
    clear_all();
}

template<class object_type>
std::size_t queue<object_type>::get_size(){
    return size;
}

template<class object_type>
void queue<object_type>::enqueue(object_type object){
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
object_type queue<object_type>::dequeue(){
    if(size == 0) return NULL;

    size--;

    object_type returned;

    if(size == 0){
        node *tmp = begin;

        begin = NULL;
        end = NULL;

        returned = tmp->value;

        delete tmp;
    }
    else{
        node *tmp = begin;

        begin = begin->next_node;

        returned = tmp->value;

        delete tmp;
    }

    return returned;
}

template<class object_type>
void queue<object_type>::clear_all(){
    for(std::size_t i{0}; i < size; i++) dequeue();
}

#endif
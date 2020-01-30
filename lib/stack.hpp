#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

//-------------------- Определение класса --------------------

template<class object_type>
class stack
{
public:
    stack();

    ~stack();

    std::size_t get_size();
    
    void push(object_type);

    object_type pop();

    void clear_all();

private:
    struct node
    {
        object_type value;

        node *previous_node;
        node *next_node;
    };

    std::size_t size;

    node *begin;
    node *end;
};

//-------------------- Реализация класса --------------------

template<class object_type>
stack<object_type>::stack(){
    size = 0;

    begin = NULL;
    end = NULL;
}

template<class object_type>
stack<object_type>::~stack(){
    clear_all();
}

template<class object_type>
std::size_t stack<object_type>::get_size(){
    return size;
}

template<class object_type>
void stack<object_type>::push(object_type object){
    if(begin == NULL){
        begin = new node;

        begin->previous_node = NULL;

        end = begin;
    }
    else{
        end->next_node = new node;

        end->next_node->previous_node = end;

        end = end->next_node;
    }

    end->value = object;
    end->next_node = NULL;

    size++;
}

template<class object_type>
object_type stack<object_type>::pop(){
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
        node *tmp = end;

        end = end->previous_node;
        end->next_node = NULL;

        returned = tmp->value;

        delete tmp;
    }

    return returned;
}

template<class object_type>
void stack<object_type>::clear_all(){
    for(std::size_t i{0}; i < size; i++) pop();
}

#endif
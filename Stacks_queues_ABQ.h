//
// Created by ISABE on 2/12/2024.
//

#ifndef LAB4_P2_ABQ_H
#define LAB4_P2_ABQ_H
#include <iostream>
#include <stdexcept>

template<typename T>
class ABQ {

private:
    T* data;
    T* new_data;
    unsigned int max_capacity;
    unsigned int current_size;
    float scale_factor;


public:
    ABQ();

    ABQ(int capacity);

    ABQ(const ABQ &d);

    ABQ &operator=(const ABQ &d);

    ~ABQ();

    void resize_array(int newer_capacity);

    void enqueue(T some_data);

    T dequeue();

    T peek();

    //Accessor functions
    unsigned int getSize();

    unsigned int getMaxCapacity();

    T* getData();

};

//Implementations

//Default Constructor
template<typename T>
ABQ<T>::ABQ(){
    max_capacity = 1;
    current_size = 0;
    scale_factor = 2.0f;

    data = new T[max_capacity];

}

//Specified capacity constructor
template<typename T>
ABQ<T>::ABQ(int capacity){
    max_capacity = capacity;
    current_size = 0;
    scale_factor = 2.0f;

    data = new T[max_capacity];

}

//Copy constructor
template<typename T>
ABQ<T>::ABQ(const ABQ<T> &d) {
    max_capacity = d.max_capacity;
    current_size = d.current_size;
    scale_factor = d.scale_factor;

    data = new T[max_capacity];
    for (unsigned int i = 0; i < current_size; ++i) {
        data[i] = d.data[i];
    }

}

//Assignment operator
template<typename T>
ABQ<T> &ABQ<T>::operator=(const ABQ<T> &d) {
    if (this != &d) {
        delete[] data;
        max_capacity = d.max_capacity;
        current_size = d.current_size;
        scale_factor = d.scale_factor;
        data = new T[max_capacity];
        for (unsigned int i = 0; i < current_size; ++i) {
            data[i] = d.data[i];
        }
    }
    return *this;
}

//Destructor
template<typename T>
ABQ<T>::~ABQ(){
    delete [] data;

}

//Resizing array
template<typename T>
void ABQ<T>::resize_array(int newer_capacity) {
    new_data = new T[newer_capacity];
    for (unsigned int i = 0; i < current_size; ++i){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    max_capacity = newer_capacity;
}

//add item to the end of que function
template<typename T>
void ABQ<T>::enqueue(T some_data) {
    if (current_size == max_capacity){
        resize_array(max_capacity * scale_factor);
    }
    data[current_size++] = some_data;
}

//Removes front item
template<typename T>
T ABQ<T>::dequeue() {
    if (current_size == 0) {
        throw std::runtime_error("An error has occurred.");
    }
    T front_item = data[0];
    for (unsigned int i = 1; i < current_size; ++i) {
        data[i - 1] = data[i];
    }
    --current_size;
    if (current_size < max_capacity / scale_factor) {
        resize_array(max_capacity / scale_factor);
    }
    return front_item;

}
//Returns front item value
    template<typename T>
    T ABQ<T>::peek() {
        if (current_size == 0) {
            throw std::runtime_error("An error has occurred.");
        }
        return data[0];
    }

//Accessor Functions
    template<typename T>
    unsigned int ABQ<T>::getMaxCapacity() {
        return max_capacity;
    }

    template<typename T>
    unsigned int ABQ<T>::getSize() {
        return current_size;
    }

    template<typename T>
    T *ABQ<T>::getData() {
        return data;
    }

#endif //LAB4_P2_ABQ_H

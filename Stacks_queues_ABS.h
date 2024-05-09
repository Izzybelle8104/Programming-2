//
// Created by ISABE on 2/11/2024.
//

#ifndef LAB4_ABS_H
#define LAB4_ABS_H
#include <iostream>
#include <stdexcept>

template<typename T>
class ABS {

private:
    T* data;
    T* new_data;
    unsigned int max_capacity;
    unsigned int current_size;
    float scale_factor;


public:
    ABS();

    ABS(int capacity);

    ABS(const ABS &d);

    ABS &operator=(const ABS &d);

    ~ABS();

    void resize_array(int newer_capacity);

    void push(T some_data);

    T pop();

    T peek();

    //Accessor functions
    unsigned int getSize();

    unsigned int getMaxCapacity();

    T* getData();

};

//Implementations

//Default Constructor
template<typename T>
ABS<T>::ABS(){
    max_capacity = 1;
    current_size = 0;
    scale_factor = 2.0f;

    data = new T[max_capacity];

}

//Specified capacity constructor
template<typename T>
ABS<T>::ABS(int capacity){
    max_capacity = capacity;
    current_size = 0;
    scale_factor = 2.0f;

    data = new T[max_capacity];

}

//Copy constructor
template<typename T>
ABS<T>::ABS(const ABS<T> &d) {
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
ABS<T> &ABS<T>::operator=(const ABS<T> &d) {
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
ABS<T>::~ABS(){
    delete [] data;

}

//Resizing array
template<typename T>
void ABS<T>::resize_array(int newer_capacity) {
    new_data = new T[newer_capacity];
    for (unsigned int i = 0; i < current_size; ++i){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    max_capacity = newer_capacity;
}

//Push function
template<typename T>
void ABS<T>::push(T some_data) {
    if (current_size == max_capacity){
        resize_array(max_capacity * scale_factor);
    }
    this->data[current_size++] = some_data;
}

//Removes top item
template<typename T>
T ABS<T>::pop() {
    if (current_size == 0){
        throw std::runtime_error("An error has occurred.");
    }
    T popped_item = data[--current_size];
    if ( current_size < max_capacity / scale_factor) {
        resize_array(max_capacity / scale_factor);
    }

    return popped_item;
}

//Returns top item value
template<typename T>
T ABS<T>::peek() {
    if (current_size == 0){
        throw std::runtime_error("An error has occurred.");
    }
    return data[current_size - 1];
}

//Accessor Functions
template<typename T>
unsigned int ABS<T>::getMaxCapacity() {
    return max_capacity;
}

template<typename T>
unsigned int ABS<T>::getSize() {
    return current_size;
}

template<typename T>
T* ABS<T>::getData() {
    return data;
}

#endif //LAB4_ABS_H

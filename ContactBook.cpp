
#include "ContactBook.h"
#include <iostream>
#include <string>
#include <algorithm>

//class Contact {
//    // Write the class
//private:
//    std::string _name;
//    std::string _number;

//public:

//constructor
Contact::Contact(std::string name, std::string number){
    _name = name;
    _number = number;
}

//other functions
std::string Contact::getName() {

    return _name;
}

std::string Contact::getNumber(){

    return _number;
}

void Contact::C_Display(){

    std::cout << _name << ", " << _number << std::endl;

}

//CLASS 2

//class ContactBook {
//    //pointers only
//private:
//    static const int MAX_SIZE = 100;
//    Contact* contacts[MAX_SIZE];
//    unsigned int curr_size = 0;


//Constructor
ContactBook::ContactBook() {

}

Contact* ContactBook::Find(const std::string& search){
    for (unsigned int i= 0; i< curr_size; ++i) {
        if (contacts[i]->getName() == search) {
            return contacts[i];
        }

        if (contacts[i]->getNumber() == search) {
            return contacts[i];
        }
    }

    return nullptr;
}

void ContactBook::Add(Contact& contact){
    *this += contact;
}

void ContactBook::AddContacts(std::vector<Contact*>& vector_contacts) {
    //Takes in a vector of contact pointers, and stores all of its values in the class’s array,
    //in the same order that they were in the vector. It returns nothing
    for (unsigned int i = 0; i < vector_contacts.size(); ++i){
        *this += *vector_contacts[i];
    }
}

void ContactBook::Remove(Contact& contact) {
    *this -= contact;
}

void ContactBook::Display() {
    for (unsigned int i = 0; i < curr_size; ++i) {
        contacts[i]->C_Display();
    }
}

void ContactBook::Alphabetize() {
    //- sorts the array in alphabetical order based on contact name. Note that in this special
    //case, Albert would come before Alberta. This should be the only function that can alter the order
    //that the contacts are stored in the array.
    std::sort(contacts, contacts + curr_size,
              [](Contact* a, Contact* b) {
                  return a->getName() + a->getNumber() < b->getName() + b->getNumber();
              });

    }

//Operators
ContactBook& ContactBook::operator+=(Contact& contact) {
    if (curr_size < MAX_SIZE) {
        contacts[curr_size] = &contact;
        ++curr_size;
    }

    return *this;
}

ContactBook& ContactBook::operator+=(ContactBook& otherBook) {
    //Adds all contacts from the passed in ContactBook to this object. Adding
    //them to the back in the order they are in the other ContactBook’s array.
    for (unsigned int i = 0; i < otherBook.curr_size; ++i){
        *this += *otherBook.contacts[i];
    }

    return *this;
}

ContactBook ContactBook::operator+(ContactBook& otherBook){
    //Adds two contact books together and returns the resulting ContactBook.
    ContactBook newbook = *this;
    newbook += otherBook;

    return newbook;
}

ContactBook& ContactBook::operator-=(Contact& contact) {
    //Removes the Contact that matches the passed-in Contact

    for (unsigned int i = 0; i < curr_size; ++i) {
        if (contacts[i] == &contact) {
            // Shift elements to fill the gap
            for (unsigned int j = i; j < curr_size - 1; ++j) {
                contacts[j] = contacts[j + 1];
            }
            --curr_size;

        }
    }
    return *this;
}
ContactBook& ContactBook::operator-=(ContactBook& otherBook) {
    // Removes all contacts from a passed in ContactBook from this object
    for (unsigned int i = 0; i < otherBook.curr_size; ++i){
        *this -= *otherBook.contacts[i];
    }
    return *this;
}
ContactBook ContactBook::operator-(ContactBook& otherBook)  {
    //returns a new ContactBook object as the result instead
    //of modifying the current one
    ContactBook newBook = *this;
    newBook -= otherBook;
    return newBook;

}
bool ContactBook::operator==(ContactBook& otherBook) {
    //Equality operator, if two ContactBooks have all the same Contacts in
    //them, in any order. Meaning that contacts may not exactly be in the same order in both
    //arrays in each of the ContactBooks
    if (curr_size != otherBook.curr_size) {
        return false;
    }

    // Check if all contacts in this book exist in the other book
    for (unsigned int i = 0; i < curr_size; ++i) {
        bool contactFound = false;

        for (unsigned int j = 0; j < otherBook.curr_size; ++j) {
            if (contacts[i]->getName() == otherBook.contacts[j]->getName() &&
                contacts[i]->getNumber() == otherBook.contacts[j]->getNumber()) {
                contactFound = true;
                break;
            }
        }

        if (!contactFound) {
            return false;
        }
    }

    return true;

}

bool ContactBook::operator!=(ContactBook& otherBook) {
    //Same as above, but the not equal operator
    return !(*this == otherBook);



}


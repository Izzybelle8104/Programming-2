//
// Created by ISABE on 2/28/2024.
//

#ifndef P1_LINKED_LISTS_LINKEDLIST_H
#define P1_LINKED_LISTS_LINKEDLIST_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;


template<typename T>
class LinkedList {

//public variables ------------------------------------------------------
public:
    //Node
    struct Node{
        T data;

        Node* next;

        Node* prev;

        //No parameters constructor
        Node(){
            data = "";
            next = nullptr;
            prev = nullptr;
        }

        //Parameterized constructor
        Node(T data) {
            this->data = data;
            next = nullptr;
            prev = nullptr;
        }
    };

    // Big 3 stuff ------------------------------------------------------------------------

    //Default Constructor
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    //Copy Constructor
    LinkedList(const LinkedList& other){
        //initialize
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;

        //copy the nodes
        Node* current = other.head;
        while (current != nullptr) {
            AddTail(current->data);
            current = current->next;
        }

    }

    //Destructor
    ~LinkedList(){
        Clear();
    }

    //Behaviors ------------------------------------------------------------------------

    void PrintForward() {
        Node* current = head;

        while (current != nullptr){
            cout << current->data << endl;
            current = current->next;
        }
    }

    void PrintReverse(){
        Node* current = tail;

        while (current != nullptr){
            cout << current->data << endl;
            current = current->prev;
        }

    }

    void PrintForwardRecursive(Node* start){
        if (start == nullptr) {
            return;
        }

        cout << start->data << endl;

        PrintForwardRecursive(start->next);
    }

    void PrintReverseRecursive(Node* end){
        if (end == nullptr) {
            return;
        }

        cout << end->data << endl;

        PrintReverseRecursive(end->prev);

    }


    //Accessors ------------------------------------------------------------------------

    int NodeCount(){

        return size;
    }

    void FindAll(vector<Node*>& storage,const T& value) {
        //find nodes that match value and store a pointer to that node in the passed in vector
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value){
                storage.push_back(current);
            }
            current = current->next;
        }
    }

    Node* Find(const T& data) const{
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data){
                return current;
            }
            current = current->next;
        }

        return nullptr;
}

    Node* GetNode(int index) const {
        if (index < 0 or index >= size){
            throw out_of_range("Index out of range");
        }

        Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }

        return current;
    }



    Node* Head(){

        return head;
    }

    Node* Tail(){

        return tail;
    }

    //Insertions ------------------------------------------------------------------------

    void AddHead(const T& data){
        if (size == 0) {
            head = new Node(data);
            tail = head;
        }

        else{
            Node* newNode = new Node(data);
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        size++;
    }

    void AddTail(const T& data){
        if (size == 0) {
            head = new Node(data);
            tail = head;
        }

        else{
            Node* newNode = new Node(data);
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        size++;

    }

    void AddNodesHead(const T* arr, int amount){
        for (int i=0; i < amount; i++){
            AddHead(arr[i]);
        }
    }

    void AddNodesTail(const T* arr, int amount){
        for (int i=0; i < amount; i++){
            AddTail(arr[i]);
        }
    }

    void InsertAfter(Node* node,const T& value){
        Node* after = node->next;
        Node* insert = new Node(value);

        node->next= insert;
        insert->prev = node;

        if (after == nullptr){
            tail = insert;
        }
        else{
            insert->next = after;
            after->prev = insert;
        }

        size++;
    }

    void InsertBefore(Node* node,const T& value){
        Node* before = node->prev;
        Node* insert = new Node(value);

        insert->prev = before;
        insert->next = node;

        if (before == nullptr){
            head = insert;
        }
        else{
            before->next = insert;
            node->prev = insert;
        }

        size++;
    }

    void InsertAt(const T& value, int index){
        if (index < 0 or index > size){
            throw out_of_range("Index out of range");
        }

        Node* current = head;
        Node* before = nullptr;

        for (int i=0; i < index; ++i){
            before = current;
            current = current->next;
        }


        if (index == 0 or before == nullptr){
            InsertBefore(current, value);
        }

        else if (index == size){
            InsertAfter(tail, value);
        }

        else {
            InsertAfter(before, value);
        }

    }


    // Removals ------------------------------------------------------------------------

    bool RemoveHead(){
        if (head == nullptr){
            //empty list
            return false;
        }

        Node* adjust = head->next;

        if(adjust == nullptr){
            //one in list
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else{
            adjust->prev = nullptr;
            delete head;
            head = adjust;
        }
        size--;
        return true;

    }

    bool RemoveTail(){
        if (tail == nullptr){
            //empty list
            return false;
        }

        Node* adjust = tail->prev;

        if (adjust == nullptr){
            //one in list
            delete tail;
            head = nullptr;
            tail = nullptr;
        }

        else {
            delete tail;
            tail = adjust;
            tail->next = nullptr;
        }

        size--;
        return true;
    }

    int Remove(T& value){
        int count = 0;
        Node* test = head;
        while (test != nullptr){
            Node* nextNode = test->next;
            if (test->data == value){
                Node* before = test->prev;
                Node* after = test->next;

                if (before == nullptr and after == nullptr){
                    //one item in list
                    delete test;
                    head = nullptr;
                    tail = nullptr;
                }
                else if(before == nullptr){
                    //remove head
                    after->prev = nullptr;
                    head = after;
                    delete test;
                }
                else if(after == nullptr){
                    //remove tail
                    before->next = nullptr;
                    tail = before;
                    delete test;
                }
                else{
                    before->next = after;
                    after->prev = before;
                    delete test;
                }

                size--;
                count++;

                }
            test = nextNode;
        }
      return count;
    }

    bool RemoveAt(int index){
        if (index < 0 or index >= size){
            return false;
        }

        Node* current = GetNode(index);

        if (current->prev == nullptr) {
            // Removing the head
            head = current->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (current->next == nullptr) {
            // Removing the tail
            tail = current->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;  // Delete the node at the given index
        size--;  // Adjust the size of the list
        return true;

    }

    void Clear(){
        Node* current = head;

        while (current != nullptr){
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }


    //Operators ------------------------------------------------------------------------

    T& operator[](int index){
        Node* node = GetNode(index);

        return node->data;
    }

    LinkedList& operator=(const LinkedList& other){
        //self assignment
        if (this == &other){
            return *this;
        }

        //clean slate
        Clear();

        //copy the nodes
        Node* current = other.head;
        while (current != nullptr){
            AddTail(current->data);
            current = current->next;
        }

        }

    bool operator==(const LinkedList& other) const {
        if (size != other.size){
            return false;
        }

        Node* currentcompare = head;
        Node* othercompare = other.head;
        while (currentcompare != nullptr and othercompare != nullptr){
            if (currentcompare-> data != othercompare->data){
                return false;
            }

            currentcompare = currentcompare->next;
            othercompare = othercompare->next;
        }

        return true;
    }

//Private variables -----------------------------------------------------------------
private:
    Node* head;
    Node* tail;
    unsigned int size{};


};
#endif //P1_LINKED_LISTS_LINKEDLIST_H

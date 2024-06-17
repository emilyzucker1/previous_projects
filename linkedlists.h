//
// Created by Emily Zucker on 2/9/24.
//

#ifndef PRACTICE_LINKEDLISTS_H
#define PRACTICE_LINKEDLISTS_H

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
class LinkedList{

    unsigned int current_size; // size of current list

public:

    struct Node{ // nested struct to create nodes for the list.

        T data;
        Node* prev;
        Node* next;

        Node(){
            prev = nullptr;
            next = nullptr;
        }

        Node(Node& other){
            data = other->data;
            prev = other->prev;
            next = other->next;
        }

    };

    Node* head;
    Node* tail;

    LinkedList();
    LinkedList(const LinkedList<T>& other_list);
    ~LinkedList();

    void PrintForward();
    void PrintReverse();
    void PrintForwardRecursive(Node* start);
    void PrintReverseRecursive(Node* start);

    unsigned int NodeCount();
    void FindAll(vector<Node*>& saved_data, T search_for);
    Node* Find(T search_for) const;
    Node* GetNode(int index) const;
    Node* getHead();
    Node* getTail();

    void AddHead(T data);
    void AddTail(T data);
    void AddNodesHead(T array[], int size);
    void AddNodesTail(T array[], int size);
    void InsertAfter(Node* indicated_node, T data);
    void InsertBefore(Node* indicated_node, T data);
    void InsertAt(T data, int index);

    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(T search_for);
    bool RemoveAt(int index);
    void Clear();

    T operator[](int index);
    LinkedList<T>& operator=(const LinkedList<T> other_list);
    bool operator==(const LinkedList<T> other_list);




};


template <typename T>
LinkedList<T>::LinkedList() {
    current_size = 0;
    head = nullptr;
    tail = nullptr;
}


template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other_list) {
    current_size = 0;
    head = new Node();
    head->data = other_list.head->data;
    current_size++;
    Node* current_node = head;
    Node* current_copy = other_list.head->next;
    while (current_size < (other_list.current_size - 1)){
        Node* new_node = new Node();
        new_node->data = current_copy->data;
        current_node->next = new_node;
        new_node->prev = current_node;
        current_node = new_node;
        current_copy = current_copy->next;
        current_size++;
    }
    tail = new Node();
    tail->data = other_list.tail->data;
    current_node->next = tail;
    tail->prev = current_node;
    current_size++;
}


template <typename T>
LinkedList<T>::~LinkedList(){
    if (current_size == 1){
        delete head;
    }
    else if (current_size == 0){
        head = nullptr;
        tail = nullptr;
        current_size = 0;
    }
    else {
        Node* current_node = tail;
        Node* prev_node;
        while (current_size > 1) {
            prev_node = current_node->prev;
            delete current_node;
            current_size--;
            current_node = prev_node;
        }
        delete current_node;
        current_size--;
    }
}



template <typename T>
void LinkedList<T>::PrintForward() {
    Node* current_node = head;
    for (int i = 0; i < current_size; i++){
        cout << current_node->data << endl;
        current_node = current_node->next;
    }
}


template <typename T>
void LinkedList<T>::PrintReverse() {
    Node* current_node = tail;
    for (int i = 0; i < current_size; i++){
        cout << current_node->data << endl;
        current_node = current_node->prev;
    }
}


template <typename T>
void LinkedList<T>::PrintForwardRecursive(Node* start){
    if (start != nullptr){
        cout << start->data << endl;
        PrintForwardRecursive(start->next);
    }
}


template <typename T>
void LinkedList<T>::PrintReverseRecursive(Node* start){
    if (start != nullptr){
        cout << start->data << endl;
        PrintReverseRecursive(start->prev);
    }
}


template <typename T>
unsigned int LinkedList<T>::NodeCount() {
    return current_size;
}


template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& saved_data, T search_for) {
    if (current_size == 0) {
        throw runtime_error("The list is empty.");
    }
    Node *current_node = head;
    for (int i = 0; i < current_size; i++) {
        if (current_node->data == search_for) {
            saved_data.push_back(current_node);
        }
        current_node = current_node->next;
    }
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(T search_for) const{
    if (current_size == 0){
        throw runtime_error("The list is empty.");
    }
    Node* current_node = head;
    for (int i = 0; i < current_size; i++){
        if (current_node->data == search_for){
            return current_node;
        }
        current_node = current_node->next;
    }
    return nullptr;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(int index) const{
    if (index == 0){
        return head;
    }
    else if (index == (current_size - 1)){
        return tail;
    }
    else if (index >= current_size){
        throw out_of_range("this index is out of range.");
    }
    else{
        Node* current_node = head->next;
        for (int i = 1; index < current_size; i++){
            if (i == index){
                return current_node;
            }
            else{
                current_node = current_node->next;
            }
        }
    }
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() {
    return head;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
    return tail;
}


template <typename T>
void LinkedList<T>::AddHead(T data) {
    if (current_size == 0){
        head = new Node();
        head->data = data;
        current_size++;
    }
    else if (head == nullptr){
        head = new Node();
        head->data = data;
        Node* current_node = tail;
        for (int i = current_size; i > 0; i--){
            current_node = current_node->prev;
        }
        head->next = current_node;
        current_node->prev = head;
    }
    else{
        Node* new_head = new Node();
        new_head->data = data;
        new_head->next = head;
        head->prev = new_head;
        head = new_head;
        current_size++;
        if (current_size == 2){
            tail = head->next;
        }
    }
}


template <typename T>
void LinkedList<T>::AddTail(T data) {
    if (current_size == 0){
        head = new Node();
        head->data = data;
        current_size++;
    }
    else if (current_size == 1){
        tail = new Node();
        tail->data = data;
        head->next = tail;
        tail->prev = head;
        current_size++;
    }
    else{
        Node* new_tail = new Node();
        tail->next = new_tail;
        new_tail->prev = tail;
        tail = new_tail;
        new_tail->data = data;
        current_size++;
    }
}


template <typename T>
void LinkedList<T>::AddNodesHead(T array[], int size) {
    if (current_size == 0){
        head = new Node();
        head->data = array[0];
        current_size++;
        Node* current_node = head;
        for (int i = 0; i < size - 1; i++){
            Node* new_node = new Node();
            new_node->data = array[i];
            new_node->prev = current_node;
            current_node->next = new_node;
            current_node = new_node;
            current_size++;
        }
        tail = current_node;
    }
    else{
        Node* current_node = head;
        for (int i = size; i > 0; i--) {
            Node *new_node = new Node();
            new_node->data = array[i - 1];
            current_node->prev = new_node;
            new_node->next = current_node;
            current_node = new_node;
            head = current_node;
            current_size++;
        }
    }
}


template <typename T>
void LinkedList<T>::AddNodesTail(T array[], int size) {
    if (current_size == 0){
        head = new Node();
        head->data = array[0];
        current_size++;
        Node* current_node = head;
        for (int i = 0; i < size; i++){
            Node* new_node = new Node();
            new_node->data = array[i];
            new_node->prev = current_node;
            current_node->next = new_node;
            current_node = new_node;
            current_size++;
        }
        tail = current_node;
    }
    else{
        Node* current_node = tail;
        for (int i = 0; i < size; i++){
            Node* new_node = new Node();
            new_node->data = array[i];
            current_node->next = new_node;
            new_node->prev = current_node;
            current_node = new_node;
            tail = current_node;
            current_size++;
        }
    }
}


template <typename T>
void LinkedList<T>::InsertAfter(Node* indicated_node, T data){
    Node* new_node = new Node();
    new_node->data = data;
    Node* current_node = head;
    Node* indicated_next = nullptr;
    for (int i = 0; i < current_size; i++){
        if (current_node == indicated_node){
            indicated_next = current_node->next;
            break;
        }
        current_node = current_node->next;

    }
    current_size++;
    if (indicated_next != nullptr && current_node != tail){
        indicated_next->prev = new_node;
        indicated_node->next = new_node;
        new_node->prev = indicated_node;
        new_node->next = indicated_next;
    }
    else if (indicated_next == nullptr && current_node == tail){
        current_node->next = new_node;
        new_node->prev = current_node;
    }
    else{
        throw runtime_error("Node not found.");
    }
}


template <typename T>
void LinkedList<T>::InsertBefore(Node* indicated_node, T data){
    Node* new_node = new Node();
    new_node->data = data;
    Node* current_node = head;
    Node* indicated_prev = nullptr;
    for (int i = 0; i < current_size; i++){
        if (current_node == indicated_node){
            indicated_prev = current_node->prev;
            break;
        }
        current_node = current_node->next;

    }
    current_size++;
    if (indicated_prev != nullptr && current_node != head){
        indicated_prev->next = new_node;
        indicated_node->prev = new_node;
        new_node->prev = indicated_prev;
        new_node->next = indicated_node;
    }
    else if (indicated_prev == nullptr && current_node == head){
        current_node->prev = new_node;
        new_node->next = current_node;
    }
    else{
        throw runtime_error("Node not found.");
    }
}


template <typename T>
void LinkedList<T>::InsertAt(T data, int index){
    if (index > current_size || index < 0){
        throw out_of_range("Index out of range.");
    }
    else if (index == current_size){
        AddTail(data);
    }
    else if (index == 0){
        AddHead(data);
    }
    else {
        Node *current_node = head;
        for (int i = 0; i < index; i++) {
            current_node = current_node->next;
        }
        InsertBefore(current_node, data);
    }
}


template <typename T>
bool LinkedList<T>::RemoveHead(){
    if (current_size == 0){
        return false;
    }
    else{
        Node* next = head->next;
        delete head;
        head = next;
        current_size--;
        return true;
    }
}


template <typename T>
bool LinkedList<T>::RemoveTail(){
    if (current_size == 0){
        return false;
    }
    else{
        Node* previous = tail->prev;
        delete tail;
        tail = previous;
        current_size--;
        return true;
    }
}

template <typename T>
unsigned int LinkedList<T>::Remove(T search_for){
    unsigned int removed_count = 0;
    if (current_size == 0){
        return removed_count;
    }
    else{
        Node* current_node = head;
        Node* next_node;
        Node* prev_node;
        for (int i = current_size; i > 0; i--){
            if (current_node->data == search_for){
                next_node = current_node->next;
                prev_node = current_node->prev;
                delete current_node;
                current_node = next_node;
                current_node->prev = prev_node;
                prev_node->next = current_node;
                removed_count++;
                current_size--;
            }
            else{
                current_node = current_node->next;
            }
        }
        return removed_count;
    }
}


template <typename T>
bool LinkedList<T>::RemoveAt(int index){
    if (current_size == 0 || index >= current_size){
        return false;
    }
    else{
        Node* current_node = head;
        for (int i = 0; i < index; i ++){
            current_node = current_node->next;
        }
        Node* next = current_node->next;
        Node* prev = current_node->prev;
        delete current_node;
        next->prev = prev;
        prev->next = next;
        current_size--;
        return true;
    }
}


template <typename T>
void LinkedList<T>::Clear(){
    if (current_size == 1){
        delete head;
        current_size = 0;
    }
    else if (current_size == 0){
        head = nullptr;
        tail = nullptr;
        current_size = 0;
    }
    else {
        Node* current_node = tail;
        Node* prev_node;
        while (current_size > 1) {
            prev_node = current_node->prev;
            delete current_node;
            current_size--;
            current_node = prev_node;
        }
        delete current_node;
        current_size--;
        head = nullptr;
        tail = nullptr;
        current_size = 0;
    }
}


template <typename T>
T LinkedList<T>::operator[](int index) {
    if (current_size == 0){
        throw out_of_range("Index out of Range.");
    }
    Node* current_node = head;
    for (int i = 0; i < index; i++){
        if (current_node->next == nullptr){
            throw out_of_range("Index out of Range.");
        }
        else{
            current_node = current_node->next;
        }
    }
    T data = current_node->data;
    return data;
}


template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> other_list){
    if (current_size == 1){
        delete head;
    }
    else {
        Node* current_node;
        while (current_size > 1) {
            current_node = tail->prev;
            delete current_node->next;
            current_size--;
            tail = current_node;
        }
        delete current_node;
        current_size--;
    }
    head = new Node();
    head->data = other_list.head->data;
    current_size++;
    Node* current_node = head;
    Node* current_copy = other_list.head->next;
    while (current_size < (other_list.current_size - 1)){
        Node* new_node = new Node();
        new_node->data = current_copy->data;
        current_node->next = new_node;
        new_node->prev = current_node;
        current_node = new_node;
        current_copy = current_copy->next;
        current_size++;
    }
    tail = new Node();
    tail->data = other_list.tail->data;
    current_node->next = tail;
    tail->prev = current_node;
    current_size++;
    return *this;
}


template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> other_list){
    if (current_size != other_list.current_size){
        return false;
    }
    else{
        Node* current_node = head;
        Node* other_node = other_list.head;
        for (int i = 0; i < current_size; i++){
            if (current_node->data != other_node->data){
                return false;
            }
            current_node = current_node->next;
            other_node = other_node->next;
        }
        return true;
    }
}



#endif //PRACTICE_LINKEDLISTS_H

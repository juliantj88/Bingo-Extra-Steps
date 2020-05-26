#include "LinkedList.h"
#include <fstream>

Node::Node(char data, Node* next){
    Node::data = data;
    Node::next = next;
}

LinkedList::LinkedList(){
    head = nullptr;
}

int LinkedList::size(){
    int count = 0;
    Node* current = head;
    while(current != nullptr){
        ++count;
        current = current->next;
    }

    return count;
}

char LinkedList::getValue(int index){
    int count = 0;
    Node* current = head;
    char returnValue = ' ';

    if (index < size()){
        while (count < index){
            count++;
            current = current->next;
        }
        returnValue = current->data;
    } 
    else {
        throw std::out_of_range("Linked list getValue attempt out of range");
    }

    return returnValue;
}

void LinkedList::addFront(char data){
    Node* newNode = new Node(data, nullptr);
    newNode->next = head;
    head = newNode;
}

void LinkedList::addBack(char data){
    Node* newNode = new Node(data, nullptr);
    Node* current = head;
    //int count = 0;
    if(current == nullptr){
        head = newNode;
    } else {
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::removeFront(){
    head = head->next;
}

void LinkedList::removeBack(){
    if (head->next == nullptr) {
        removeFront();
     } else {
        Node* prev = nullptr;
        Node* current = head;

        while (current->next != nullptr) {
           prev = current;
           current = current->next;
        }

        prev->next = current->next;
        delete current;
     }
}

void LinkedList::clear(){
    Node* current = head;
    Node* nextNode = nullptr;
    if(head->next == nullptr){
        head = nullptr;
    } else {
        while(current != nullptr)
        nextNode = current->next;
        current = nullptr;
        current = nextNode;
    }
}
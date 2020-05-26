#ifndef LINKEDLIST_H
#define LINKEDLIST_H


class Node{
    public:
        Node(char data, Node* next);
        char data;
        Node *next;
};

class LinkedList{
    private:
        Node *head;

    public:
        LinkedList();

        LinkedList(const LinkedList& otherList);

        ~LinkedList();

        int size();

        char getValue(int index);

        void addFront(char data);

        void addBack(char data);

        void removeFront();

        void removeBack();

        void clear();
};

#endif // LINKEDLIST_H
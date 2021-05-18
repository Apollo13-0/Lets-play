#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "Node.h"

using namespace std;

template <class T>
class List {
private:
    Node<T> *head;
    int size;

public:
    List();

    ~List(){};

    bool isEmpty();

    void insertLast(T);

    void insertFirst(T);

    void deleteNode(T);

    void printList();

    Node<T>* find(int pos);

    bool findValue(T);

    int getSize();

    void delete_all();
};



#endif //LIST_H

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <class T>
class Node {
private:
    Node *next;
    T value;

public:
    Node();

    Node(T);

    ~Node();
    Node *getNext() const;

    void setNext(Node *next);

    T getValue() const;

    void setValue(T value);

    void printNode();

    void delete_all();
};


#endif //NODE_H

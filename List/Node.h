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
    Node(){
        value = NULL;
        next = NULL;
    };

    Node(T value_){
        value = value_;
        next = NULL;
    };

    ~Node(){};
    Node *getNext() const{
        return next;
    };

    void setNext(Node *next_){
        Node::next = next_;
    };

    T getValue() const{
        return value;
    };

    void setValue(T value_){
        Node::value = value_;
    };

    void printNode(){
        //cout << "Node-> " << "Dato: " << dato << " Direcion: " << this << " Siguiente: " << next << endl;
        cout << value << "-> ";
    };

    void delete_all(){
        if (next)
            next->delete_all();
        delete this;
    };
};


#endif //NODE_H

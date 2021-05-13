#include "Node.h"

// Constructor por defecto
template<typename T>
Node<T>::Node()
{
    value = NULL;
    next = NULL;
}

// Constructor por parámetro
template<typename T>
Node<T>::Node(T value_)
{
    value = value_;
    next = NULL;
}

template<typename T>
Node<T>::~Node() {}

template<class T>
Node<T> *Node<T>::getNext() const {
    return next;
}

template<class T>
void Node<T>::setNext(Node *next_) {
    Node::next = next_;
}

template<class T>
T Node<T>::getValue() const {
    return value;
}

template<class T>
void Node<T>::setValue(T value_) {
    Node::value = value_;
}

// Imprimir un Nodo
template<typename T>
void Node<T>::printNode() {
    //cout << "Node-> " << "Dato: " << dato << " Direcion: " << this << " Siguiente: " << next << endl;
    cout << value << "-> ";
}
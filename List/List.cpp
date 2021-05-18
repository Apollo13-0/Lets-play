#include "List.h"
#include "Node.h"
#include "Node.cpp"


using namespace std;


// Constructor por defecto
template<typename T>
List<T>::List()
{
    size = 0;
    head = NULL;
}
template<typename  T>
bool List<T>::isEmpty()
{
    return head == NULL;
}

// Insertar al inicio
template<typename  T>
void List<T>::insertFirst(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = head;

    if (isEmpty()) {
        head = new_node;
    } else {
        new_node->setNext(head);
        head = new_node;

        while (temp) {
            temp = temp->getNext();
        }
    }
    size++;
}


// Insertar al final
template<typename  T>
void List<T>::insertLast(T data_) {
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = head;

    if (isEmpty()) {
        head = new_node;
    } else {
        while (temp->getNext() != NULL) {
            temp = temp->getNext();
        }
        temp->setNext(new_node);
    }
    size++;
}

// Eliminar por data del nodo
template<typename  T>
void List<T>::deleteNode(T data_) {
    Node<T> *temp = head;
    Node<T> *temp1 = head->getNext();

    if (head->getValue() == data_) {
        head = temp->getNext();
    } else {
        while (temp1) {
            if (temp1->getValue() == data_) {
                Node<T> *aux_node = temp1;
                temp->setNext(temp1->getNext());
                delete aux_node;
                size--;
            }
            temp = temp->getNext();
            temp1 = temp1->getNext();
        }
    }
}

// Imprimir la Lista
template<typename  T>
void List<T>::printList() {
    Node<T> *temp = head;
    if (isEmpty()) {
        cout << "La Lista está vacía " << endl;
    } else {
        while (temp) {
            temp->printNode();
            if (!temp->getNext()) cout << "NULL";
            temp = temp->getNext();
        }
    }
    cout << endl << endl;
}

template<typename  T>
Node<T>* List<T>::find(int pos) {
    Node<T> *current = head;
    int count = 0;
    while (current != NULL){
        if (count == pos){
            return current;
        } else {
            count++;
            current = current->getNext();
        }
    }
}

template<typename  T>
int List<T>::getSize()
{
    return size;
}

template<typename  T>
bool List<T>::findValue(T value_) {
    Node<T> *current = head;
    bool result = false;
    while (current != NULL){
        if (value_ == current->getValue()){
            result = true;
            return result;
        } else {
            result = false;
            current = current->getNext();
        }
    }
}

template<typename  T>
void List<T>::delete_all()
{
    head->delete_all();
    head = 0;
    size = 0;
}


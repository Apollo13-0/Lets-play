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
    List(){
        size = 0;
        head = NULL;
    };

    ~List(){};

    bool isEmpty(){
        return head == NULL;
    };

    void insertLast(T data_){
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
    };

    void insertFirst(T data_){
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
    };

    void deleteNode(T data_){
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
    };

    void printList(){
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
    };

    Node<T>* find(int pos){
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
    };

    bool findValue(T value_){
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
    };

    int getSize(){
        return size;
    };

    void delete_all(){
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->getNext();
            delete temp;
        }
        head = 0;
        size = 0;
    };
};



#endif //LIST_H

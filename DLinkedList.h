#pragma once
#include <iostream>
#include <stdexcept>
#include "List.h"
#include "DNode.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E>* head;
    DNode<E>* current;
    DNode<E>* tail;
    int size;

public:
    DLinkedList() {
        head = new DNode<E>(nullptr, nullptr);
        tail = new DNode<E>(nullptr, head);
        head->next = tail;
        current = head;
        size = 0;
    }

    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }

    void insert(E element) override {
        DNode<E>* newNode =
            new DNode<E>(element, current->next, current);
        current->next->previous = newNode;
        current->next = newNode;
        size++;
    }

    void append(E element) override {
        DNode<E>* newNode =
            new DNode<E>(element, tail, tail->previous);
        tail->previous->next = newNode;
        tail->previous = newNode;
        size++;
    }

    void setElement(E element) override {
        if (current->next == tail)
            throw runtime_error("No current element.");
        current->next->element = element;
    }

    E getElement() override {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        return current->next->element;
    }

    E remove() override {
        if (size == 0)
            throw runtime_error("List is empty.");
        if (current->next == tail)
            throw runtime_error("No current element.");
        DNode<E>* temp = current->next;
        E result = temp->element;
        current->next = temp->next;
        temp->next->previous = current;
        delete temp;
        size--;
        return result;
    }

    void clear() override {
        current = head;
        while (head->next != tail) {
            DNode<E>* temp = head->next;
            head->next = temp->next;
            temp->next->previous = head;
            delete temp;
        }
        tail->previous = head;
        current = head;
        size = 0;
    }

    void goToStart() override {
        current = head;
    }

    void goToEnd() override {
        current = tail->previous;
    }

    void goToPos(int pos) override {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of bounds.");
        if (pos <= size / 2) {
            current = head;
            for (int i = 0; i < pos; i++) {
                current = current->next;
            }
        }
        else {
            current = tail->previous;
            for (int i = size; i > pos; i--) {
                current = current->previous;
            }
        }
    }

    void next() override {
        if (current->next != tail)
            current = current->next;
    }

    void previous() override {
        if (current != head)
            current = current->previous;
    }

    bool atStart() override {
        return current == head;
    }

    bool atEnd() override {
        return current->next == tail;
    }

    int getPos() override {
        DNode<E>* temp = head;
        int pos = 0;
        while (temp != current) {
            temp = temp->next;
            pos++;
        }
        return pos;
    }

    int getSize() override {
        return size;
    }

    void print() override {
        DNode<E>* temp = head->next;
        cout << "[ ";
        while (temp != tail) {
            cout << temp->element << " ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
};

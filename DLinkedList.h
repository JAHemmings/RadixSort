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
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail new DNode<E>(nullptr, head);
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}
	void insert(E element) {
		current->next = current->next->previous = new DNode(element, current->next, current);
		size++;
	}
	void append(E element) {
		tail->previous = tail->previous->next = new DNode(element, tail, tail->previous);
		size++;
	}
	void setElement(E element) {
	if (current->next==tail)
		throw runtime_error("No current element.");
	current->next->element = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty");
		if (current->next == tail)
			throw runtime_error("No Current element.");
		E result = current->next->element;
		current->next=current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return result;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current->next == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->previous;
		}
		current = tail->previous = head;
		size = 0;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail->previous;
	}
	void goToPos(int pos) {
		if (pos<0||pos>size)
			throw runtime_error("Index out of bounds");
		if (pos <=size /2) {
			current = head;
			for (int i = 0; i < pos; i++) current = current->next;
		}
		else {
			current = tail->previous;
			for (int i = 0; i < size-pos; i++) current = current->previous;
		}
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head)
			current = current->previous;
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current-next == tail;
	}
	int getPos() {
		DNode<E>* temp = head;
		int pos = 0;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
};
#include "LinkedList.h"
#include "Node.h"

template <typename T>
void LinkedList<T>::add(T element) {
	Node<T>* newNode = new Node<T>(element);

	if (head == nullptr) {
		head = newNode;
		return;
	}

	Node<T>* temp = head;
	while (temp->next != nullptr)
		temp = temp->next;

	temp->next = newNode;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* current = head;
	while (current != nullptr) {
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
}


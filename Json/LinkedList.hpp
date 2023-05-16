#pragma once
#include <iostream>
#include "IIterator.hpp"

template <typename T>
class LinkedList {
	class Node {
	public:
		T value;
		Node* next = nullptr;

		Node() = default;
		Node(const T& value);
		Node(T&& value);
	};

	Node* head = nullptr;
	Node* tail = nullptr;

	void free();
	void copyFrom(const LinkedList& other);
	void moveFrom(LinkedList&& other);

public:
	class LinkedListIterator : public IIterator<T> {
		Node* node = nullptr;
	public:
		LinkedListIterator(Node* node);
		LinkedListIterator& operator++() override;
		bool operator!=(const IIterator<T>& other) const override;
		bool operator!=(const LinkedListIterator& other) const;
		T& operator*() const override;

		~LinkedListIterator() override = default;
	};

	LinkedList() = default;
	LinkedList(const LinkedList& other);
	LinkedList(LinkedList&& other);
	LinkedList<T>& operator=(const LinkedList& other);
	LinkedList<T>& operator=(LinkedList&& other);
	~LinkedList();

	LinkedListIterator begin() const;
	LinkedListIterator end() const;

	void add(const T& element);
	void add(T&& element);
	bool isEmpty() const;

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll);

	friend class JsonHashMap;
};

template <typename T>
LinkedList<T>::LinkedListIterator::LinkedListIterator(Node* node) : node(node) {}

template <typename T>
typename LinkedList<T>::LinkedListIterator& LinkedList<T>::LinkedListIterator::operator++() {
	if (node != nullptr)
		node = node->next;

	return *this;
}

template <typename T>
T& LinkedList<T>::LinkedListIterator::operator*() const {
	return node->value;
}

template <typename T>
bool LinkedList<T>::LinkedListIterator::operator!=(const IIterator<T>& other) const {
	return other != *this;
}

template <typename T>
bool LinkedList<T>::LinkedListIterator::operator!=(const LinkedListIterator& other) const {
	return node != other.node;
}

template <typename T>
typename LinkedList<T>::LinkedListIterator LinkedList<T>::begin() const {
	return LinkedListIterator(head);
}

template <typename T>
typename LinkedList<T>::LinkedListIterator LinkedList<T>::end() const {
	return LinkedListIterator(nullptr);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll) {
	typename LinkedList<T>::Node* temp = ll.head;

	while(temp != nullptr) {
		os << temp->value << " ";
		temp = temp->next;
	}
	return os;
}

template<typename T>
LinkedList<T>::Node::Node(const T& _value) {
	value = _value;
}
template<typename T>
LinkedList<T>::Node::Node(T&& _value) {
	value = std::move(_value);
}

template <typename T>
void LinkedList<T>::add(T&& element) {
	Node* newNode = new Node(std::move(element));

	if (head == nullptr) {
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = tail->next;
}

template <typename T>
void LinkedList<T>::add(const T& element) {
	Node* newNode = new Node(element);

	if (head == nullptr) {
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = tail->next;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
	copyFrom(other);
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other) {
	moveFrom(std::move(other));
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	free();
}

template <typename T>
void LinkedList<T>::free() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = tail = nullptr;
}

template<typename T>
void LinkedList<T>::copyFrom(const LinkedList& other) {
	if (other.isEmpty())
		return;

	head = tail = new Node(other.head->value);

	Node* tempOther = other.head->next;

	while (tempOther != nullptr) {
		tail->next = new Node(tempOther->value);
		tail = tail->next;
		tempOther = tempOther->next;
	}
}

template<typename T>
void LinkedList<T>::moveFrom(LinkedList&& other) {
	head = other.head;
	tail = other.tail;

	other.head = other.tail = nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return head == nullptr;
}







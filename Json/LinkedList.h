#pragma once
#include "Node.h"
#include "UniquePointer.h"

template <typename T>
class LinkedList {
	UniquePointer<Node<T>> head = nullptr;

	void free();
	void copyFrom(const LinkedList& other);
	void moveFrom(LinkedList&& other);

public:
	LinkedList() = default;
	LinkedList(const LinkedList& other);
	LinkedList<T>& operator=(const LinkedList& other);
	LinkedList<T>& operator=(LinkedList&& other);
	~LinkedList();

	void add(T element);
};




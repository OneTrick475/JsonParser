#pragma once

template <typename T>
class Node {
public:
	T value;
	Node* next = nullptr;

	Node() = default;
	Node(T value);
};



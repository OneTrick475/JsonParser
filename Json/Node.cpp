#include "Node.h"
#include "UniquePointer.h"
#include "JsonPair.h"

template class Node<UniquePointer<JsonPair>>;
template class Node<int>;


template <typename T>
Node<T>::Node(T _value) {
	value = _value;
}

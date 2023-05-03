#include "UniquePointer.h"
#include <utility>
#include "MyString.h"
#include "JsonPair.h"
#include "Node.h"

template class UniquePointer<int>;
template class UniquePointer<MyString>;
template class UniquePointer<JsonPair>;
template class UniquePointer<Node<JsonPair>>;

template<typename T>
UniquePointer<T>::UniquePointer(T* ptr) {
	this->ptr = ptr;
}

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) noexcept {
	move(std::move(other));
}

template<typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& other) noexcept {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template<typename T>
T* UniquePointer<T>::operator->() {
	return ptr;
}

template<typename T>
const T* UniquePointer<T>::operator->() const {
	return ptr;
}

template<typename T>
T& UniquePointer<T>::operator*() {
	return *ptr;
}

template<typename T>
const T& UniquePointer<T>::operator*() const {
	return *ptr;
}

template<typename T>
T* UniquePointer<T>::get() {
	return this->ptr;
}

template<typename T>
void UniquePointer<T>::reset(T* ptr) {
	if (this->ptr == ptr) {
		return;
	}

	free();
	this->ptr = ptr;
}

template<typename T>
T* UniquePointer<T>::release() {
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

template<typename T>
UniquePointer<T>::~UniquePointer() {
	free();
}

template<typename T>
void UniquePointer<T>::move(UniquePointer&& other) noexcept {
	ptr = other.ptr;
	other.ptr = nullptr;
}

template<typename T>
void UniquePointer<T>::free() {
	delete ptr;
}
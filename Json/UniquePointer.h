//from the github of Georgi Terziev
//modified to a template class by me
#pragma once

template<typename T>
class UniquePointer {
private:
	T* ptr;
public:
	UniquePointer(T* ptr);
	UniquePointer(const T& ptr) = delete;
	UniquePointer& operator=(const T& ptr) = delete;

	UniquePointer(UniquePointer&& other) noexcept;
	UniquePointer& operator=(UniquePointer&& other) noexcept;

	T* operator->();
	const T* operator->() const;
	T& operator*();
	const T& operator*() const;

	T* get();
	void reset(T* ptr);
	T* release(); // releases the ownership of the pointer

	~UniquePointer();
private:
	void move(UniquePointer&& other) noexcept;
	void free();
};


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
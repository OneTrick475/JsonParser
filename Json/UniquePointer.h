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


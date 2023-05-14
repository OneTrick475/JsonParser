#pragma once

template <typename T>
class IIterator {
public:
	virtual IIterator& operator++() = 0;
	virtual bool operator!=(const IIterator& other) const = 0;
	virtual T& operator*() const = 0;

	virtual ~IIterator() = default;
};
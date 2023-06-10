#pragma once
#include <functional>
#include "Vector.hpp"
#include "LinkedList.hpp"

namespace HashMapConstants {
	const size_t initialVectorLen = 64;
}

template <typename keyType, typename valueType, typename hashFunc = std::hash<keyType>>
class HashMap {
public:
	class Pair {
	public:
		keyType key;
		valueType value;
		Pair() = default;
		Pair(keyType key, valueType value);
		bool operator==(const Pair& other);
	};
private:
	size_t dataCapacity = HashMapConstants::initialVectorLen;
	Vector<LinkedList<Pair>> data;
	hashFunc hash;
public:

	class MapIterator : IIterator<Pair> {
		typename LinkedList<Pair>::LinkedListIterator iter = nullptr;
		const HashMap* map;
		size_t linkedListIndex = 0;
	public:
		MapIterator(typename LinkedList<Pair>::LinkedListIterator iter, size_t linkedListIndex, const HashMap* map);
		MapIterator& operator++() override;
		bool operator!=(const IIterator<Pair>& other) const override;
		bool operator!=(const MapIterator& other) const;
		Pair& operator*() const override;

		~MapIterator() override = default;
		friend class HashMap;
	};

	HashMap();
	HashMap(size_t dataCapacity);

	MapIterator begin() const;
	MapIterator end() const;

	void put(keyType key, valueType value);
	const valueType& at(const keyType& key) const;
	valueType& at(const keyType& key);
	void remove(const keyType& key);

	valueType& operator[](const keyType& key);
	const valueType& operator[](const keyType& key) const;
};


template<typename keyType, typename valueType, typename hashFunc>
HashMap<keyType, valueType, hashFunc>::Pair::Pair(keyType key, valueType value) : key(key), value(value) {}


template<typename keyType, typename valueType, typename hashFunc>
HashMap<keyType, valueType, hashFunc>::MapIterator::MapIterator(typename LinkedList<Pair>::LinkedListIterator iter, 
	size_t linkedListIndex, const HashMap* map) : iter(iter), linkedListIndex(linkedListIndex), map(map) {}


template<typename keyType, typename valueType, typename hashFunc>
typename HashMap<keyType, valueType, hashFunc>::MapIterator& HashMap<keyType, valueType, hashFunc>::MapIterator::operator++(){
	if (++iter != map->data[linkedListIndex].end()) {
		return *this;
	}

	while (linkedListIndex < map->dataCapacity - 1) {
		linkedListIndex++;
		if (!map->data[linkedListIndex].isEmpty()) {
			iter = map->data[linkedListIndex].begin();
			return *this;
		}
	}

	*this = map->end();
	return *this;
}


template<typename keyType, typename valueType, typename hashFunc>
bool HashMap<keyType, valueType, hashFunc>::MapIterator::operator!=(const IIterator<Pair>& other) const {
	return other != *this;
}

template<typename keyType, typename valueType, typename hashFunc>
bool HashMap<keyType, valueType, hashFunc>::MapIterator::operator!=(const MapIterator& other) const {
	return iter != other.iter;
}


template<typename keyType, typename valueType, typename hashFunc>
typename HashMap<keyType, valueType, hashFunc>::Pair& HashMap<keyType, valueType, hashFunc>::MapIterator::operator*() const {
	return *iter;
}

template<typename keyType, typename valueType, typename hashFunc>
HashMap<keyType, valueType, hashFunc>::HashMap() : data(HashMapConstants::initialVectorLen){}

template<typename keyType, typename valueType, typename hashFunc>
HashMap<keyType, valueType, hashFunc>::HashMap(size_t dataCapacity) : dataCapacity(dataCapacity), data(dataCapacity) {}


template<typename keyType, typename valueType, typename hashFunc>
typename HashMap<keyType, valueType, hashFunc>::MapIterator HashMap<keyType, valueType, hashFunc>::begin() const {
	for (size_t i = 0; i < dataCapacity; i++) {
		if (!data[i].isEmpty())
			return MapIterator(data[i].begin(), i, this);
	}
	return end();
}

template<typename keyType, typename valueType, typename hashFunc>
typename HashMap<keyType, valueType, hashFunc>::MapIterator HashMap<keyType, valueType, hashFunc>::end() const {
	return MapIterator(nullptr, dataCapacity, nullptr);
}

template<typename keyType, typename valueType, typename hashFunc>
void HashMap<keyType, valueType, hashFunc>::put(keyType key, valueType value) {
	size_t index = hash(key) % dataCapacity;

	if (data[index].isEmpty()) {
		data[index].add(Pair(key, value));
		return;
	}

	for(typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key) {
			pair.value = value;
			return;
		}
	}

	data[index].add(Pair(key, value));
}


template <typename keyType, typename valueType, typename hashFunc>
const valueType& HashMap<keyType, valueType, hashFunc>::at(const keyType& key) const {
	size_t index = hash(key) % dataCapacity;

	for(typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
	throw std::range_error("key doesnt exist");
}

template <typename keyType, typename valueType, typename hashFunc>
valueType& HashMap<keyType, valueType, hashFunc>::at(const keyType& key) {
	size_t index = hash(key) % dataCapacity;

	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
	throw std::range_error("key doesnt exist");
}


template <typename keyType, typename valueType, typename hashFunc>
valueType& HashMap<keyType, valueType, hashFunc>::operator[](const keyType& key) {
	size_t index = hash(key) % dataCapacity;

	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
	put(key, valueType());
	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
}

template <typename keyType, typename valueType, typename hashFunc>
const valueType& HashMap<keyType, valueType, hashFunc>::operator[](const keyType& key) const {
	size_t index = hash(key) % dataCapacity;

	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
	put(key, valueType());
	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key)
			return pair.value;
	}
}


template <typename keyType, typename valueType, typename hashFunc>
void HashMap<keyType, valueType, hashFunc>::remove(const keyType& key) {
	size_t index = hash(key) % dataCapacity;

	for (typename LinkedList<Pair>::LinkedListIterator it = data[index].begin(); it != data[index].end(); ++it) {
		Pair& pair = *it;
		if (pair.key == key) {
			data[index].remove(pair);
			return;
		}
	}
}


template <typename keyType, typename valueType, typename hashFunc>
bool HashMap<keyType, valueType, hashFunc>::Pair::operator==(const Pair& other) {
	return key == other.key;
}





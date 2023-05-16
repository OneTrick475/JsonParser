#include "JsonHashMap.h"
#include "Vector.hpp"
#include "JsonPair.h"
#include "LinkedList.hpp"
#include <iostream>

JsonHashMap::JsonHashMap() : data(JsonHashMapConstants::initialVectorLen) {}

JsonHashMap::JsonHashMap(size_t dataCapacity) : dataCapacity(dataCapacity), data(dataCapacity) {}

size_t JsonHashMap::hash(const MyString& str) const {
	size_t index = -1; //this is done to set it to the max value

	for (size_t i = 0; i < str.length(); i++)
		index -= str[i];

	return index % dataCapacity;
}

void JsonHashMap::put(const JsonPair& pair) {
	size_t index = hash(pair.key);

	if (data[index].head == nullptr) {
		data[index].add(pair);
		return;
	}

	LinkedList<JsonPair>::Node* temp = data[index].head;

	while(temp != nullptr) {
		if(strcmp(temp->value.key.c_str(), pair.key.c_str()) == 0) {
			temp->value.value = pair.value;
			return;
		}
		temp = temp->next;
	}
	data[index].add(pair);
}

JsonHashMap::JsonIterator::JsonIterator(LinkedList<JsonPair>::LinkedListIterator iter, size_t linkedListIndex, const JsonHashMap* map) :
																			iter(iter), linkedListIndex(linkedListIndex), map(map) {}

JsonHashMap::JsonIterator JsonHashMap::begin() const {
	for(size_t i = 0; i < dataCapacity; i++) {
		if (!data[i].isEmpty()) 
			return JsonIterator(data[i].begin(), i, this);
	}
	return end();
}

JsonHashMap::JsonIterator JsonHashMap::end() const {
	return JsonIterator(nullptr, dataCapacity, nullptr);
}


JsonHashMap::JsonIterator& JsonHashMap::JsonIterator::operator++() {
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

JsonPair& JsonHashMap::JsonIterator::operator*() const {
	return *iter;
}

bool JsonHashMap::JsonIterator::operator!=(const IIterator<JsonPair>& other) const {
	return other != *this;
}

bool JsonHashMap::JsonIterator::operator!=(const JsonIterator& other) const {
	return iter != other.iter;
}


#include "JsonHashMap.h"
#include "Vector.h"
#include "JsonPair.h"
#include "LinkedList.h"
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

std::ostream& operator<<(std::ostream& os, const JsonHashMap& map) {
	os << '{' << '\n';

	bool isFirst = true;

	for(size_t i = 0; i < map.dataCapacity; i++) {
		if (!map.data[i].isEmpty()) {
			if(!isFirst) {
				os << ",\n";
			}
			os << map.data[i];
			isFirst = false;
		}
	}
	os << "\n }";
	return os;
}
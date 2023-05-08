#pragma once
#include "Vector.h"
#include "JsonPair.h"
#include "LinkedList.h"
#include "MyString.h"

namespace JsonHashMapConstants {
	const size_t initialVectorLen = 64;
}

class JsonHashMap {
	size_t dataCapacity = JsonHashMapConstants::initialVectorLen;
	Vector<LinkedList<JsonPair>> data;

	size_t hash(const MyString& str) const;

public:
	JsonHashMap();
	JsonHashMap(size_t dataCapacity);

	void put(const JsonPair& pair);

	friend std::ostream& operator<<(std::ostream& os, const JsonHashMap& map);
};

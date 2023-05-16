#pragma once
#include "Vector.hpp"
#include "JsonPair.h"
#include "LinkedList.hpp"
#include "MyString.h"

namespace JsonHashMapConstants {
	const size_t initialVectorLen = 64;
}

class JsonHashMap {
	size_t dataCapacity = JsonHashMapConstants::initialVectorLen;
	Vector<LinkedList<JsonPair>> data;

	size_t hash(const MyString& str) const;

public:
	class JsonIterator : IIterator<JsonPair> {
		LinkedList<JsonPair>::LinkedListIterator iter = nullptr;
		const JsonHashMap* map;
		size_t linkedListIndex = 0;
	public:
		JsonIterator(LinkedList<JsonPair>::LinkedListIterator iter, size_t linkedListIndex, const JsonHashMap* map);
		JsonIterator& operator++() override;
		bool operator!=(const IIterator<JsonPair>& other) const override;
		bool operator!=(const JsonIterator& other) const;
		JsonPair& operator*() const override;

		~JsonIterator() override = default;
		friend class JsonHashMap;
	};

	JsonHashMap();
	JsonHashMap(size_t dataCapacity);

	JsonIterator begin() const;
	JsonIterator end() const;

	void put(const JsonPair& pair);
};

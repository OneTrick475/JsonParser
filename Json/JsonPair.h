#pragma once
#include "MyString.h"
#include "JsonValue.h"

class JsonPair {
	MyString key;
	JsonValue value;

public:
	JsonPair() = default;
	JsonPair(const MyString& key, const JsonValue& value);

	friend std::ostream& operator<<(std::ostream& os, const JsonPair& pair);
	friend class JsonHashMap;
};




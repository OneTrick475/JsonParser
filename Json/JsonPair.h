#pragma once
#include "MyString.h"
#include "ValueType.h"
#include "JsonValue.h"

class Json;

class JsonPair {
	MyString key;
	JsonValue value;
	valueType type;

	void copyFrom(const JsonPair& other);
	void moveFrom(const JsonPair& other);
	void free();

public:
	JsonPair();
	JsonPair(const JsonPair& other);
	JsonPair(JsonPair&& other);
	JsonPair& operator=(const JsonPair& other);
	JsonPair& operator=(JsonPair&& other);
	~JsonPair();
};




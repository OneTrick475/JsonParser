#pragma once
#include "JsonHashMap.h"
#include "MyString.h"

class Json {
private:
	JsonHashMap map;

	void readValue(std::ifstream& file, JsonValue& value) const;
	bool readKey(std::ifstream& file, MyString& str) const;
	bool readPair(std::ifstream& file, JsonPair& pair) const;
	void readObject(std::ifstream& file, JsonHashMap& object) const;
	
public:
	Json() = default;
	Json(const MyString& fileName);

	void parse(const MyString& fileName);
};






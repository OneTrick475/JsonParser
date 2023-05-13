#pragma once
#include "JsonHashMap.h"
#include "MyString.h"

class Json {
private:
	JsonHashMap map;

	void readVector(std::istream& file, Vector<JsonValue>& vector) const;
	void inputValue(std::istream& file, JsonValue& value, const MyString& buffer) const;
	void readValue(std::istream& file, JsonValue& value) const;
	bool readKey(std::istream& file, MyString& str) const;
	bool readPair(std::istream& file, JsonPair& pair) const;
	void readObject(std::istream& file, JsonHashMap& object) const;
	
public:
	Json() = default;
	Json(const MyString& fileName);

	void parse(const MyString& fileName);

	friend std::ostream& operator<<(std::ostream& os, const Json& json);
};






#pragma once
#include "JsonHashMap.h"
#include "MyString.h"

class Json {
private:
	JsonHashMap map;
	MyString currentFile;

	void readVector(std::istream& file, Vector<JsonValue>& vector) const;
	void readValue(std::istream& file, JsonValue& value, MyString& buffer) const;
	void readKey(MyString& buffer, MyString& str) const;
	bool readPair(std::istream& file, JsonPair& pair) const;
	void readObject(std::istream& file, JsonHashMap& object) const;
	
public:
	Json() = default;
	Json(const MyString& fileName);

	void parse(const MyString& fileName);
	void print() const;
	void save(const MyString& path= "\0") const;

	friend std::ostream& operator<<(std::ostream& os, const Json& json);
};






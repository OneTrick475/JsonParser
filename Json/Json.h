#pragma once
#include "HashMap.hpp"
#include "MyString.h"
#include "JsonValue.h"

class Json {
private:
	HashMap<MyString, JsonValue, hash> map;
	MyString currentFile;

	void readVector(std::istream& file, Vector<JsonValue>& vector) const;
	void readValue(std::istream& file, JsonValue& value, MyString& buffer) const;
	void readKey(MyString& buffer, MyString& str) const;
	bool readPair(std::istream& file, MyString& str, JsonValue& value) const;
	void readObject(std::istream& file, HashMap<MyString, JsonValue, hash>& object) const;
	
public:
	Json() = default;
	Json(const MyString& fileName);

	void search(const MyString& key) const;
	void find(const MyString& key) const;
	void set(const MyString& path, const MyString& value);

	void parse(const MyString& fileName);
	void print() const;
	void save(const MyString& path = "\0") const;

	friend std::ostream& operator<<(std::ostream& os, const Json& json);
};





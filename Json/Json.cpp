#include "Json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "BoolValue.h"
#include "DoubleValue.h"
#include "MyString.h"
#include "HashMap.hpp"
#include "IntValue.h"
#include "StringValue.h"

Json::Json(const MyString& fileName) {
	parse(fileName);
}

void Json::parse(const MyString& fileName) {
	std::ifstream file(fileName.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	MyString buffer;

	getline(file, buffer, '\n');

	buffer.trim();

	if (strcmp(buffer.c_str(), "{") != 0)
		throw std::invalid_argument("Invalid Json file. Does not start with a '{' ");

	readObject(file, map.map);

	file.close();

	currentFile = fileName;
}

void Json::readObject(std::istream& file, HashMap<MyString, PolymorphicPtr<Value>, hash>& object) const {
	while(true) {
		MyString key;
		PolymorphicPtr<Value> value;
		if (!readPair(file, key, value))
			break;
		object.put(key, value);
	}
}

void Json::readKey(MyString& buffer, MyString& str) const{
	std::stringstream ss(buffer.c_str());

	MyString key;
	getline(ss, key, ':');
	getline(ss, buffer, '\n');

	buffer.trim();

	if (key[0] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not start with \" ");

	if (key[key.length() - 1] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not end with \" ");

	str = MyString(&key.c_str()[1], key.length() - 2); // we want to skip the first  "  and the  "  at the end

}

void Json::readVector(std::istream& file, Vector<PolymorphicPtr<Value>>& vector) const {
	MyString buffer;
	getline(file, buffer, '\n');
	buffer.trim();

	while(strcmp(buffer.c_str(), "]") != 0) {
		PolymorphicPtr<Value> value;
		readValue(file, value, buffer);
		vector.pushBack(value);
		getline(file, buffer, '\n');
		buffer.trim();
	}
}

void Json::readValue(std::istream& file, PolymorphicPtr<Value>& value, MyString& buffer) const {
	if (buffer.c_str()[buffer.length() - 1] == ',')
		buffer = MyString(buffer.c_str(), buffer.length() - 1);

	if (buffer.isNumber()) {
		value = new IntValue();
		value->setValue(buffer.toNumber());
	}

	else if(buffer.isDouble()) {
		value = new DoubleValue();
		value->setValue(buffer.toDouble());
	}

	else if (buffer[0] == '{') {
		HashMap<MyString, PolymorphicPtr<Value>, hash> object;
		readObject(file, object);
		value = new ObjectValue();
		value->setValue(object);
	}

	else if (buffer[0] == '[') {
		Vector<PolymorphicPtr<Value>> vector;
		readVector(file, vector);
		value = new VectorValue();
		value->setValue(vector);
	}

	else if (buffer[0] == '"' && buffer[buffer.length() - 1] == '"') {
		value = new StringValue();
		value->setValue(MyString(&buffer.c_str()[1], buffer.length() - 2));
	}

	else if (strcmp(buffer.c_str(), "false") == 0) {
		value = new BoolValue();
		value->setValue(false);
	}

	else if (strcmp(buffer.c_str(), "true") == 0) {
		value = new BoolValue();
		value->setValue(true);
	}

	else
		throw std::runtime_error("Invalid Json file.");
}

bool Json::readPair(std::istream& file, MyString& key, PolymorphicPtr<Value>& value) const {
	MyString buffer;
	getline(file, buffer, '\n');
	buffer.trim();

	if (strcmp(buffer.c_str(), "}") == 0 || strcmp(buffer.c_str(), "},") == 0)
		return false;

	readKey(buffer, key); // takes the key out of buffer

	buffer.trim();
	readValue(file, value, buffer);

	return true;
}

std::ostream& operator<<(std::ostream& os, const Json& json) {
	json.map.write(os);
	return os;
}

void Json::print() const {
	std::cout << *this;
}

void Json::save(const MyString& path) const {
	std::ofstream file(currentFile.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	file << *this;
}

void Json::search(const MyString& key) const {
	std::cout << "[\n";
	map.search(key);
	std::cout << "]";
}

void Json::find(const MyString& key) const {
	map.find(key);
}

void Json::set(const MyString& path, const MyString& value) {
	PolymorphicPtr<Value> val;
	MyString buffer;
	std::stringstream ss(value.c_str());
	getline(ss, buffer, '\n');
	readValue(ss, val, buffer);

	map.set(path, val);
}

void Json::create(const MyString& path, const MyString& value) {
	PolymorphicPtr<Value> val;
	MyString buffer;
	std::stringstream ss(value.c_str());
	getline(ss, buffer, '\n');
	readValue(ss, val, buffer);

	map.create(path, val);
}


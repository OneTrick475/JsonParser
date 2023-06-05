#include "Json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyString.h"
#include "JsonValue.h"
#include "HashMap.hpp"

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

	readObject(file, map);

	file.close();

	currentFile = fileName;
}

void Json::readObject(std::istream& file, HashMap<MyString, JsonValue, hash>& object) const {
	while(true) {
		MyString key;
		JsonValue value;
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

void Json::readVector(std::istream& file, Vector<JsonValue>& vector) const {
	MyString buffer;
	getline(file, buffer, '\n');
	buffer.trim();

	while(strcmp(buffer.c_str(), "]") != 0) {
		JsonValue value;
		readValue(file, value, buffer);
		vector.pushBack(value);
		getline(file, buffer, '\n');
		buffer.trim();
	}
}

void Json::readValue(std::istream& file, JsonValue& value, MyString& buffer) const {
	if (buffer.c_str()[buffer.length() - 1] == ',')
		buffer = MyString(buffer.c_str(), buffer.length() - 1);

	if (buffer.isNumber())
		value.setValue(buffer.toNumber());

	else if (buffer[0] == '{') {
		HashMap<MyString, JsonValue, hash> object;
		readObject(file, object);
		value.setValue(object);
	}

	else if (buffer[0] == '[') {
		Vector<JsonValue> vector;
		readVector(file, vector);
		value.setValue(vector);
	}

	else if (buffer[0] == '"' && buffer[buffer.length() - 1] == '"')
		value.setValue(MyString(&buffer.c_str()[1], buffer.length() - 2));

	else if (strcmp(buffer.c_str(), "false") == 0)
		value.setValue(false);

	else if (strcmp(buffer.c_str(), "true") == 0)
		value.setValue(true);

	else
		throw std::runtime_error("Invalid Json file.");
}

bool Json::readPair(std::istream& file, MyString& key, JsonValue& value) const {
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
	os << '{' << '\n';

	bool isFirst = true;

	for (HashMap<MyString, JsonValue, hash>::MapIterator it = json.map.begin(); it != json.map.end(); ++it) {
		if (!isFirst) {
			os << ",\n";
		}
		os <<  "  " << (*it).key << ": ";
		(*it).value.write(os);
		isFirst = false;
	}
	os << "\n}";
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
	for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if ((*it).key == key) {
			(*it).value.write(std::cout);
			std::cout << '\n';
		}
		(*it).value.search(key);
	}
	std::cout << "]";
}

void Json::find(const MyString& key) const {
	for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if ((*it).key == key) {
			std::cout << (*it).key << " : ";
			(*it).value.write(std::cout);
			std::cout << '\n';
		}
	}
}

void Json::set(const MyString& path, const MyString& value) {
	JsonValue val;
	MyString buffer;
	std::stringstream ss(value.c_str());
	getline(ss, buffer, '\n');
	readValue(ss, val, buffer);

	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;
	if(i == path.length()) {
		for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
			if ((*it).key == path) {
				(*it).value = val;
				return;
			}
		}
		throw std::invalid_argument("Invalid path");
	}
	for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if ((*it).key == path.substr(0, i)) {
			(*it).value.set(&path.c_str()[i+1], val);
			return;
		}
	}
	throw std::invalid_argument("Invalid path");
}


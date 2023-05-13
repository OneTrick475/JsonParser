#include "Json.h"
#include "JsonHashMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "MyString.h"

Json::Json(const MyString& fileName) {
	parse(fileName);
}

void Json::parse(const MyString& fileName) {
	map = JsonHashMap();

	std::ifstream file(fileName.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	MyString buffer;

	getline(file, buffer, '\n');

	buffer.trim();

	if (strcmp(buffer.c_str(), "{") != 0)
		throw std::invalid_argument("Invalid Json file. Does not start with a '{' ");

	readObject(file, map);
}

void Json::readObject(std::istream& file, JsonHashMap& object) const {
	while(true) {
		JsonPair pair;
		if (!readPair(file, pair))
			break;
		object.put(pair);
	}
}

bool Json::readKey(std::istream& file, MyString& str) const{
	MyString buffer;
	getline(file, buffer, ':');

	buffer.trim();

	if (strcmp(buffer.c_str(), "}") == 0)
		return false;

	if (buffer[0] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not start with \" ");

	if (buffer[buffer.length() - 1] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not end with \" ");

	str = MyString(&buffer.c_str()[1], buffer.length() - 2); // we want to skip the first  "  and the  "  at the end

	return true;
}

void Json::readVector(std::istream& file, Vector<JsonValue>& vector) const {
	MyString buffer;
	getline(file, buffer, ']');

	std::stringstream ss(buffer.c_str());

	getline(ss, buffer, ',');

	size_t i = 0;

	while(strcmp(buffer.c_str(), "]") != 0) {
		inputValue(ss, vector[i++], buffer);
		getline(ss, buffer, ',');
	}
}

void Json::inputValue(std::istream& file, JsonValue& value, const MyString& buffer) const {
	if (buffer.isNumber())
		value.setValue(buffer.toNumber()); 

	else if (strcmp(buffer.c_str(), "{") == 0) {
		JsonHashMap object;
		readObject(file, object);
		value.setValue(object);
	}

	else if (strcmp(buffer.c_str(), "[") == 0) {
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


void Json::readValue(std::istream& file, JsonValue& value) const {
	MyString buffer;

	getline(file, buffer, ',');

	buffer.trim();

	inputValue(file, value, buffer);
}

bool Json::readPair(std::istream& file, JsonPair& pair) const {
	MyString key;
	if (!readKey(file, key))
		return false;

	JsonValue value;
	readValue(file, value);

	pair = JsonPair(key, value);

	return true;
}

std::ostream& operator<<(std::ostream& os, const Json& json) {
	return os << json.map;
}
#include "Json.h"
#include "JsonHashMap.h"
#include <iostream>
#include <fstream>
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

	file >> buffer;

	if (strcmp(buffer.c_str(), "{") != 0)
		throw std::invalid_argument("Invalid Json file. Does not start with a '{' ");

	readObject(file, map);
}

void Json::readObject(std::ifstream& file, JsonHashMap& object) const {
	while(true) {
		JsonPair pair;
		if (!readPair(file, pair))
			break;
		object.put(pair);
	}
}

bool Json::readKey(std::ifstream& file, MyString& str) const{
	MyString buffer;

	file >> buffer;

	if (strcmp(buffer.c_str(), "}") != 0)
		return false;

	if (buffer[0] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not start with \" ");

	if (buffer[buffer.length() - 2] != '"')
		throw std::invalid_argument("Invalid Json file. A string did not end with \" ");

	if (buffer[buffer.length() - 1] != ':')
		throw std::invalid_argument("Invalid Json file. There should be a : after each key");

	str = MyString(&buffer.c_str()[1], buffer.length() - 3); // we want to skip the first  "  and the  ":  at the end

	return true;
}

void Json::readValue(std::ifstream& file, JsonValue& value) const {
	MyString buffer;

	file >> buffer;

	if (buffer[0] == '"' && buffer[buffer.length() - 1] == '"')
		value.setValue(MyString(&buffer.c_str()[1], buffer.length() - 2));

	else if (buffer.isNumber())
		value.setValue(buffer.toNumber());


}


bool Json::readPair(std::ifstream& file, JsonPair& pair) const {
	MyString key;
	if (!readKey(file, key))
		return false;

	JsonValue value;
	readValue(file, value);

	return true;
}

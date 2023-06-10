#include "Json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "JsonParser.h"
#include "values/BoolValue.h"
#include "values/DoubleValue.h"
#include "MyString.h"
#include "data structures/HashMap.hpp"
#include "values/IntValue.h"
#include "values/StringValue.h"
#include "values/VectorValue.h"

Json::Json(const MyString& fileName) {
	parse(fileName);
}

void Json::parse(const MyString& fileName) {
	currentFile = fileName;
	map = JsonParser::parse(fileName);
}

std::ostream& operator<<(std::ostream& os, const Json& json) {
	(& json.map)->write(os);
	return os;
}

void Json::print() const {
	std::cout << *this;
}

void Json::saveAs(const MyString& filePath, const MyString& path) const {
	std::ofstream file(filePath.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	map.writeAt(file, path);

	file.close();
}

void Json::save(const MyString& path) const {
	std::ofstream file(currentFile.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	map.writeAt(file, path);

	file.close();
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
	JsonParser::readValue(ss, val, buffer);

	map.set(path, val);
}

void Json::create(const MyString& path, const MyString& value) {
	PolymorphicPtr<Value> val;
	MyString buffer;
	std::stringstream ss(value.c_str());
	getline(ss, buffer, '\n');
	JsonParser::readValue(ss, val, buffer);

	map.create(path, val);
}

void Json::deletePath(const MyString& path) {
	map.deletePath(path);
}

void Json::moveFromTo(const MyString& origin, const MyString& dest) {
	map.moveFromTo(origin, dest);
}

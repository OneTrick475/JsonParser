#include "JsonParser.h"
#include <fstream>
#include <sstream>
#include "values/BoolValue.h"
#include "values/DoubleValue.h"
#include "values/IntValue.h"
#include "values/StringValue.h"
#include "values/VectorValue.h"

ObjectValue JsonParser::parse(const MyString& fileName){
	ObjectValue map;

	std::ifstream file(fileName.c_str());

	if (!file.is_open())
		throw std::runtime_error("couldnt open file");

	MyString buffer;

	getline(file, buffer, '\n');

	buffer.trim();

	if (strcmp(buffer.c_str(), "{") != 0)
		throw std::invalid_argument("Invalid Json format. Does not start with a '{' ");

	readObject(file, map.map);

	file.close();

	return map;
}

void JsonParser::readObject(std::istream& file, HashMap<MyString, PolymorphicPtr<Value>, hash>& object){
	while (true) {
		MyString key;
		PolymorphicPtr<Value> value;
		if (!readPair(file, key, value))
			break;
		object.put(key, value);
	}
}

void JsonParser::readKey(MyString& buffer, MyString& str){
	std::stringstream ss(buffer.c_str());

	MyString key;
	getline(ss, key, ':');
	getline(ss, buffer, '\n');

	buffer.trim();

	if (key[0] != '"')
		throw std::invalid_argument("Invalid Json format. A string did not start with \" ");

	if (key[key.length() - 1] != '"')
		throw std::invalid_argument("Invalid Json format. A string did not end with \" ");

	str = MyString(&key.c_str()[1], key.length() - 2); // we want to skip the first  "  and the  "  at the end
}

void JsonParser::readVector(std::istream& file, Vector<PolymorphicPtr<Value>>& vector){
	MyString buffer;
	getline(file, buffer, '\n');
	buffer.trim();

	while (strcmp(buffer.c_str(), "]") != 0 && strcmp(buffer.c_str(), "],") != 0) {
		PolymorphicPtr<Value> value;
		readValue(file, value, buffer);
		vector.pushBack(value);
		getline(file, buffer, '\n');
		buffer.trim();
	}
}

void JsonParser::readValue(std::istream& file, PolymorphicPtr<Value>& value, MyString& buffer){
	if (buffer.c_str()[buffer.length() - 1] == ',')
		buffer = MyString(buffer.c_str(), buffer.length() - 1);

	if (buffer.isNumber()) {
		value = new IntValue();
		value->setValue(buffer.toNumber());
	}

	else if (buffer.isDouble()) {
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
		throw std::invalid_argument("Invalid Json format.");
}

bool JsonParser::readPair(std::istream& file, MyString& key, PolymorphicPtr<Value>& value){
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
#include "JsonValue.h"
#include <iostream>
#include "ValueType.h"
#include "Vector.hpp"
#include "JsonHashMap.h"

void JsonValue::free() {
	if (type == ValueType::object) {
		delete object;
	}
	else if(type == ValueType::vector) {
		delete vector;
	}
	else if (type == ValueType::string) {
		delete string;
	}
	type = ValueType::object;
	object = nullptr;
}

void JsonValue::copyFrom(const JsonValue& other) {
	if(other.type == ValueType::object && other.object == nullptr) {
		object = nullptr;
		type = ValueType::object;
	}
	else if(other.type == ValueType::object) {
		object = new JsonHashMap(*other.object);
		type = ValueType::object;
	}
	else if (other.type == ValueType::string) {
		string = new MyString(*other.string);
		type = ValueType::string;
	}
	else if(other.type == ValueType::vector) {
		vector = new Vector<JsonValue>(*other.vector);
		type = ValueType::vector;
	}
	else if(other.type == ValueType::decimal) {
		decimal = other.decimal;
		type = ValueType::decimal;
	}
	else if (other.type == ValueType::integer) {
		integer = other.integer;
		type = ValueType::integer;
	}
	else if (other.type == ValueType::boolean) {
		boolean = other.boolean;
		type = ValueType::boolean;
	}
}

void JsonValue::moveFrom(JsonValue&& other) {
	if (other.type == ValueType::object) {
		object = other.object;
		other.object = nullptr;
		type = ValueType::object;
	}
	else if (other.type == ValueType::string) {
		string = other.string;
		other.string = nullptr;
		type = ValueType::string;
	}
	else if (other.type == ValueType::vector) {
		vector = other.vector;
		other.vector = nullptr;
		type = ValueType::vector;
	}
	else if(other.type == ValueType::decimal) {
		decimal = other.decimal;
		type = ValueType::decimal;
	}
	else if (other.type == ValueType::integer) {
		integer = other.integer;
		type = ValueType::integer;
	}
	else if (other.type == ValueType::boolean) {
		boolean = other.boolean;
		type = ValueType::boolean;
	}
}

JsonValue::JsonValue() {}

JsonValue::JsonValue(const JsonValue& other) {
	copyFrom(other);
}

JsonValue::JsonValue(JsonValue&& other) {
	moveFrom(std::move(other));
}

JsonValue& JsonValue::operator=(const JsonValue& other) {
	if(this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

JsonValue& JsonValue::operator=(JsonValue&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

JsonValue::~JsonValue() {
	free();
}

ValueType JsonValue::getType() const {
	return type;
}

void JsonValue::setType(ValueType _type) {
	type = _type;
}

int JsonValue::getInt() const {
	if(type != ValueType::integer)
		throw std::logic_error("the value is not an int");
	return integer;
}

const MyString& JsonValue::getString() const {
	if (type != ValueType::string)
		throw std::logic_error("the value is not a string");
	return *string;
}

bool JsonValue::getBool() const {
	if (type != ValueType::boolean)
		throw std::logic_error("the value is not a bool");
	return boolean;
}

double JsonValue::getDecimal() const {
	if (type != ValueType::decimal)
		throw std::logic_error("the value is not a double");
	return decimal;
}

const JsonHashMap& JsonValue::getObject() const {
	if (type != ValueType::object)
		throw std::logic_error("the value is not an object");
	return *object;
}

const Vector<JsonValue>& JsonValue::getVector() const {
	if (type != ValueType::vector)
		throw std::logic_error("the value is not a vector");
	return *vector;
}

void JsonValue::setValue(int _value) {
	free();
	type = ValueType::integer;
	integer = _value;
}

void JsonValue::setValue(const MyString& _value) {
	free();
	type = ValueType::string;
	string = new MyString(_value);
}

void JsonValue::setValue(bool _value) {
	free();
	type = ValueType::boolean;
	boolean = _value;
}

void JsonValue::setValue(double _value) {
	free();
	type = ValueType::decimal;
	decimal = _value;
}

void JsonValue::setValue(const JsonHashMap& _value) {
	free();
	type = ValueType::object;
	object = new JsonHashMap(_value);
}

void JsonValue::setValue(const Vector<JsonValue>& _value) {
	free();
	type = ValueType::vector;
	vector = new Vector<JsonValue>(_value);
}

std::ostream& operator<<(std::ostream& os, const JsonValue& value) {
	if (value.type == ValueType::object && value.object == nullptr) {
		return os << "Null";
	}
	if (value.type == ValueType::object) {
		const JsonHashMap& map = value.getObject();

		os << '{' << '\n';

		bool isFirst = true;

		for (JsonHashMap::JsonIterator it = map.begin(); it != map.end(); ++it) {
			if (!isFirst) {
				os << ",\n";
			}
			os << *it;
			isFirst = false;
		}
		os << "\n }";
		return os;
	}
	if (value.type == ValueType::string) {
		return os << '"' << value.getString() << '"';
	}
	if (value.type == ValueType::vector) {
		Vector<JsonValue> values = value.getVector();

		bool isFirst = true;

		os << "[";
		for(size_t i = 0; i < values.len(); i++) {
			if(!isFirst) 
				os << ",\n" << values[i];
			
			else {
				os << "\n" << values[i];
				isFirst = false;
			}
		}
		return os << "\n";
	}
	if (value.type == ValueType::decimal) {
		return os << value.getDecimal();
	}
	if (value.type == ValueType::integer) {
		return os << value.getInt();
	}
	if (value.type == ValueType::boolean) {
		return os << std::boolalpha << value.getBool();
	}
}
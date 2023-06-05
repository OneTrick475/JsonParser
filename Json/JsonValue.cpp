#include "JsonValue.h"
#include <iostream>
#include "ValueType.h"
#include "Vector.hpp"
#include "HashMap.hpp"

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
		object = new HashMap<MyString, JsonValue, hash>(*other.object);
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

void JsonValue::setValue(const HashMap<MyString, JsonValue, hash>& _value) {
	free();
	type = ValueType::object;
	object = new HashMap<MyString, JsonValue, hash>(_value);
}

void JsonValue::setValue(const Vector<JsonValue>& _value) {
	free();
	type = ValueType::vector;
	vector = new Vector<JsonValue>(_value);
}

void JsonValue::indent(std::ostream& os, size_t number) const {
	while (number-- > 0)
		os << ' ';
}

void JsonValue::write(std::ostream& os, size_t _indent) const {
	if (type == ValueType::object && object == nullptr) 
		os << "Null";
	
	if (type == ValueType::object) {
		const HashMap<MyString, JsonValue, hash>& map = getValue<HashMap<MyString, JsonValue, hash>>();

		os << '{' << '\n';

		bool isFirst = true;

		for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
			if (!isFirst) {
				os << ",\n";
			}
			indent(os, _indent);
			os << (*it).key << ": ";
			(*it).value.write(os, _indent + 2);
			isFirst = false;
		}
		os << "\n";
		indent(os, _indent - 2);
		os << '}';
	}
	if (type == ValueType::string) {
		os << '"' << getValue<MyString>() << '"';
	}
	if (type == ValueType::vector) {
		Vector<JsonValue> values = getValue<Vector<JsonValue>>();

		bool isFirst = true;

		os << "[";
		for (size_t i = 0; i < values.len(); i++) {
			if (!isFirst) 
				os << ",";
			
			os << "\n";
			indent(os, _indent);
			values[i].write(os, _indent + 2);
			isFirst = false;
			
		}
		os << "\n";
		indent(os, _indent - 2);
		os << ']';
	}
	if (type == ValueType::decimal) {
		os << getValue<double>();
	}
	if (type == ValueType::integer) {
		os << getValue<int>();
	}
	if (type == ValueType::boolean) {
		os << std::boolalpha << getValue<bool>();
	}
}

template <>
int JsonValue::getValue<int>() const {
	return integer;
}

template <>
double JsonValue::getValue<double>() const {
	return decimal;
}

template <>
bool JsonValue::getValue<bool>() const {
	return boolean;
}

template <>
MyString JsonValue::getValue<MyString>() const {
	return *string;
}

template <>
HashMap<MyString, JsonValue, hash> JsonValue::getValue<HashMap<MyString, JsonValue, hash>>() const {
	return *object;
}

template <>
Vector<JsonValue> JsonValue::getValue<Vector<JsonValue>>() const {
	return *vector;
}

void JsonValue::search(const MyString& key) const {
	if(type == ValueType::object) {
		HashMap<MyString, JsonValue, hash> map = getValue<HashMap<MyString, JsonValue, hash>>();

		for (HashMap<MyString, JsonValue, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
			if ((*it).key == key) {
				(*it).value.write(std::cout);
				std::cout << '\n';
			}
			(*it).value.search(key);
		}
	}
	else if(type == ValueType::vector) {
		Vector<JsonValue> values = getValue<Vector<JsonValue>>();

		if (values.len() == 0 || values[0].getType() != ValueType::object)
			return;

		for(size_t i = 0; i < values.len(); i++) {
			values[i].search(key);
		}
	}
}

void JsonValue::set(const MyString& path, const JsonValue& value) {
	if (type == ValueType::object) {

		size_t i = 0;
		while (i < path.length() && path[i] != '/')
			i++;

		if (i == path.length()) {
			for (HashMap<MyString, JsonValue, hash>::MapIterator it = (*object).begin(); it != (*object).end(); ++it) {
				if ((*it).key == path) {
					(*it).value = value;
					return;
				}
			}
			throw std::invalid_argument("Invalid path");
		}
		for (HashMap<MyString, JsonValue, hash>::MapIterator it = (*object).begin(); it != (*object).end(); ++it) {
			if ((*it).key == path.substr(0, i)) {
				(*it).value.set(&path.c_str()[i + 1], value);
				return;
			}
		}
	}
	throw std::invalid_argument("Invalid path");
}

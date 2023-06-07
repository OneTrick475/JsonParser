#include "Value.h"

void Value::indent(std::ostream& os, size_t number) const {
	while (number-- > 0)
		os << ' ';
}

void Value::setValue(bool value) {
	throw std::invalid_argument("invalid path");
}

void Value::setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& _value) {
	throw std::invalid_argument("invalid path");
}

void Value::setValue(const MyString& value) {
	throw std::invalid_argument("invalid path");
}

void Value::setValue(const Vector<PolymorphicPtr<Value>>& value) {
	throw std::invalid_argument("invalid path");
}

void Value::setValue(double value) {
	throw std::invalid_argument("invalid path");
}

void Value::setValue(int value) {
	throw std::invalid_argument("invalid path");
}

void Value::set(const MyString& path, const PolymorphicPtr<Value>& value) {
	throw std::invalid_argument("invalid path");
}

void Value::search(const MyString& key) const {}

void Value::find(const MyString& key) const {}

void Value::create(const MyString& path, const PolymorphicPtr<Value>& value) {
	throw std::invalid_argument("invalid path");
}

void Value::deletePath(const MyString& path) {
	throw std::invalid_argument("invalid path");
}

void Value::moveFromTo(const MyString& origin, const MyString& dest) {
	throw std::invalid_argument("invalid path");
}

PolymorphicPtr<Value>& Value::getDestFromPath(const MyString& path) {
	throw std::invalid_argument("invalid path");
}

PolymorphicPtr<Value> Value::getOriginFromPath(const MyString& path) {
	throw std::invalid_argument("invalid path");
}






#include "Value.h"

void Value::indent(std::ostream& os, size_t number) const {
	while (number-- > 0)
		os << ' ';
}

void Value::setValue(bool value) {
	throw std::logic_error("invalid type");
}

void Value::setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& _value) {
	throw std::logic_error("invalid type");
}

void Value::setValue(const MyString& value) {
	throw std::logic_error("invalid type");
}

void Value::setValue(const Vector<PolymorphicPtr<Value>>& value) {
	throw std::logic_error("invalid type");
}

void Value::setValue(double value) {
	throw std::logic_error("invalid type");
}

void Value::setValue(int value) {
	throw std::logic_error("invalid type");
}

void Value::set(const MyString& path, const PolymorphicPtr<Value>& value) {
	throw std::logic_error("invalid path");
}

void Value::search(const MyString& key) const {}






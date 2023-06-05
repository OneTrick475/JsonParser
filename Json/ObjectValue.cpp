#include "ObjectValue.h"

Value* ObjectValue::clone() const {
    return new ObjectValue(*this);
}

void ObjectValue::setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& value) {
	map = value;
}

void ObjectValue::write(std::ostream& os, size_t _indent) const {
	os << '{' << '\n';

	bool isFirst = true;

	for (HashMap<MyString, PolymorphicPtr<Value>, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if (!isFirst) {
			os << ",\n";
		}
		indent(os, _indent);
		os << (*it).key << ": ";
		(*(*it).value).write(os, _indent + 2);
		isFirst = false;
	}
	os << "\n";
	indent(os, _indent - 2);
	os << '}';
}

void ObjectValue::set(const MyString& path, const PolymorphicPtr<Value>& value) {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		for (HashMap<MyString, PolymorphicPtr<Value>, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
			if ((*it).key == path) {
				(*it).value = value;
				return;
			}
		}
		throw std::invalid_argument("Invalid path");
	}
	for (HashMap<MyString, PolymorphicPtr<Value>, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if ((*it).key == path.substr(0, i)) {
			(*(*it).value).set(&path.c_str()[i + 1], value);
			return;
		}
	}
	throw std::invalid_argument("Invalid path");
}

void ObjectValue::search(const MyString& key) const {
	for (HashMap<MyString, PolymorphicPtr<Value>, hash>::MapIterator it = map.begin(); it != map.end(); ++it) {
		if ((*it).key == key) {
			(*(*it).value).write(std::cout);
			std::cout << '\n';
		}
		(*(*it).value).search(key);
	}
}



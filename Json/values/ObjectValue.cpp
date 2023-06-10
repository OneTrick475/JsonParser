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
		os << "\"" << (*it).key << "\"" << ": ";
		(*it).value->write(os, _indent + 2);
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
		try {
			map.at(path) = value;
			return;
		} catch (std::range_error& ex) {
			throw std::invalid_argument("Invalid path");
		}
	}
	try {
		map.at(path.substr(0, i))->set(&path.c_str()[i + 1], value);
	}
	catch (std::range_error& ex) {
		throw std::invalid_argument("Invalid path");
	}
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

void ObjectValue::find(const MyString& key) const {
	try {
		map.at(key);
	}
	catch (std::range_error& ex) { return; }

	std::cout << key << " : ";
	map.at(key)->write(std::cout);
	std::cout << '\n';
}

void ObjectValue::create(const MyString& path, const PolymorphicPtr<Value>& value) {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		try {
			map.at(path);
			throw std::invalid_argument("theres an element in this location");
		}
		catch (std::range_error& ex) {
			map.put(path, value);
			return;
		}
	}
	try {
		map.at(path.substr(0, i))->create(&path.c_str()[i + 1], value);
	}
	catch (std::range_error& ex) {
		map[path.substr(0, i)] = PolymorphicPtr<Value>(new ObjectValue);
		map[path.substr(0, i)]->create(&path.c_str()[i + 1], value);
	}
}

void ObjectValue::deletePath(const MyString& path) {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		try {
			map.at(path);
			map.remove(path);
			return;
		}
		catch (std::range_error& ex) {
			throw std::invalid_argument("invalid path");
		}
	}
	try {
		map.at(path.substr(0, i))->deletePath(&path.c_str()[i + 1]);
	}
	catch (std::range_error& ex) {
		throw std::invalid_argument("invalid path");
	}
}

const PolymorphicPtr<Value>& ObjectValue::getAt(const MyString& path) const {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		try {
			return map.at(path);
		}
		catch (std::range_error& ex) {
			throw std::invalid_argument("invalid path");
		}
	}
	try {
		return map.at(path.substr(0, i))->getAt(&path.c_str()[i + 1]);
	}
	catch (std::range_error& ex) {
		throw std::invalid_argument("invalid path");
	}
}


PolymorphicPtr<Value>& ObjectValue::getDestFromPath(const MyString& path) {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		try {
			return map.at(path);
		}
		catch (std::range_error& ex) {
			throw std::invalid_argument("invalid path");
		}
	}
	try {
		return map.at(path.substr(0, i))->getDestFromPath(&path.c_str()[i + 1]);
	}
	catch (std::range_error& ex) {
		throw std::invalid_argument("invalid path");
	}
}

PolymorphicPtr<Value> ObjectValue::getOriginFromPath(const MyString& path) {
	size_t i = 0;
	while (i < path.length() && path[i] != '/')
		i++;

	if (i == path.length()) {
		try {
			PolymorphicPtr<Value> value = ((const HashMap<MyString, PolymorphicPtr<Value>, hash>)map).at(path);
			map.remove(path);
			return value;
		}
		catch (std::range_error& ex) {
			throw std::invalid_argument("invalid path");
		}
	}
	try {
		return map.at(path.substr(0, i))->getOriginFromPath(&path.c_str()[i + 1]);
	}
	catch (std::range_error& ex) {
		throw std::invalid_argument("invalid path");
	}
}


void ObjectValue::moveFromTo(const MyString& origin, const MyString& dest) {
	PolymorphicPtr<Value>& destValue = getDestFromPath(dest);
	PolymorphicPtr<Value> originValue = getOriginFromPath(origin);
	destValue = originValue;
}

void ObjectValue::writeAt(std::ostream& os, const MyString& path, size_t indent) const{
	if (strcmp(path.c_str(), "\0") == 0) {
		this->write(os);
		return;
	}

	getAt(path)->write(os);
}


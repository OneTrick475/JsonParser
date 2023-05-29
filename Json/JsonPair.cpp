#include "JsonPair.h"
#include "MyString.h"
#include "ValueType.h"

JsonPair::JsonPair(const MyString& key, const JsonValue& value) : key(key), value(value) {}

std::ostream& operator<<(std::ostream& os, const JsonPair& pair) {
	return os << '"' << pair.key << '"' << ": " << pair.value;
}
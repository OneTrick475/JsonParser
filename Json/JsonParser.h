#pragma once
#include <istream>
#include "PolymorphicPtr.hpp"
#include "data structures/Vector.hpp"
#include "values/Value.h"
#include "values/ObjectValue.h"

class JsonParser {
	static void readKey(MyString& buffer, MyString& str);
	static bool readPair(std::istream& file, MyString& str, PolymorphicPtr<Value>& value);
	static void readObject(std::istream& file, HashMap<MyString, PolymorphicPtr<Value>, hash>& object);
	static void readVector(std::istream& file, Vector<PolymorphicPtr<Value>>& vector);

public:
	static void readValue(std::istream& file, PolymorphicPtr<Value>& value, MyString& buffer) ;

	static ObjectValue parse(const MyString& fileName);
};

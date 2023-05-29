#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "ValueType.h"
#include "HashMap.hpp"

class JsonValue {
	ValueType type = ValueType::object;
	union { 
		int integer;
		double decimal;
		bool boolean;
		MyString* string;
		HashMap<MyString, JsonValue, hash>* object = nullptr;
		Vector<JsonValue>* vector;
	};

	void copyFrom(const JsonValue& other);
	void moveFrom(JsonValue&& other);
	void free();

	void indent(std::ostream& os, size_t number) const;

public:
	JsonValue();
	JsonValue(const JsonValue& other);
	JsonValue(JsonValue&& other);
	JsonValue& operator=(const JsonValue& other);
	JsonValue& operator=(JsonValue&& other);
	~JsonValue();

	ValueType getType() const;
	void setType(ValueType type);

	template <typename T>
	T getValue() const;

	template<>
	int getValue() const;

	template<>
	double getValue() const;

	template<>
	bool getValue() const;

	template<>
	Vector<JsonValue> getValue() const;

	template<>
	HashMap<MyString, JsonValue, hash> getValue() const;

	template<>
	MyString getValue() const;

	/*int getInt() const;
	const MyString& getString() const;
	bool getBool() const;
	double getDecimal() const;
	const HashMap<MyString, JsonValue, hash>& getObject() const;
	const Vector<JsonValue>& getVector() const;*/

	void setValue(int _value);
	void setValue(const MyString& _value);
	void setValue(bool _value);
	void setValue(double _value);
	void setValue(const HashMap<MyString, JsonValue, hash>& _value);
	void setValue(const Vector<JsonValue>& _value);

	void write(std::ostream& os, size_t indent = 4) const;
	friend std::ostream& operator<<(std::ostream& os, const JsonValue& value);
};

template <typename T>
T JsonValue::getValue() const {
	throw std::logic_error("invalid value");
}


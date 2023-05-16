#pragma once
#include "MyString.h"
#include "Vector.hpp"
#include "ValueType.h"

class JsonHashMap;

class JsonValue {
	ValueType type = ValueType::object;
	union {
		int integer;
		double decimal;
		bool boolean;
		MyString* string;
		JsonHashMap* object = nullptr;
		Vector<JsonValue>* vector;
	};

	void copyFrom(const JsonValue& other);
	void moveFrom(JsonValue&& other);
	void free();

public:
	JsonValue();
	JsonValue(const JsonValue& other);
	JsonValue(JsonValue&& other);
	JsonValue& operator=(const JsonValue& other);
	JsonValue& operator=(JsonValue&& other);
	~JsonValue();

	ValueType getType() const;
	void setType(ValueType type);

	int getInt() const;
	const MyString& getString() const;
	bool getBool() const;
	double getDecimal() const;
	const JsonHashMap& getObject() const;
	const Vector<JsonValue>& getVector() const;

	void setValue(int _value);
	void setValue(const MyString& _value);
	void setValue(bool _value);
	void setValue(double _value);
	void setValue(const JsonHashMap& _value);
	void setValue(const Vector<JsonValue>& _value);

	void write(std::ofstream& os, size_t indent = 4) const;
	friend std::ostream& operator<<(std::ostream& os, const JsonValue& value);
};



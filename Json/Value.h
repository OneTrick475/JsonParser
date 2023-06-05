#pragma once
#include "HashMap.hpp"
#include "MyString.h"
#include "PolymorphicPtr.hpp"

class Value {
protected:
	void indent(std::ostream& os, size_t number) const;
public:
	virtual Value* clone() const = 0;

	virtual void setValue(int value);
	virtual void setValue(const MyString& value);
	virtual void setValue(bool value);
	virtual void setValue(double value);
	virtual void setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& value);
	virtual void setValue(const Vector<PolymorphicPtr<Value>>& value);

	virtual void search(const MyString& key) const;
	virtual void set(const MyString& path, const PolymorphicPtr<Value>& value);

	virtual void write(std::ostream& os, size_t indent = 4) const = 0;

	virtual ~Value() = default;
};

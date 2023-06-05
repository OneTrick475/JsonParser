#pragma once
#include "Value.h"
#include "HashMap.hpp"
#include "PolymorphicPtr.hpp"
#include "MyString.h"

class ObjectValue : public Value {
	HashMap<MyString, PolymorphicPtr<Value>, hash> map;
public:
	Value* clone() const override;
	void setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& value) override;
	void write(std::ostream& os, size_t indent) const override;
	void set(const MyString& path, const PolymorphicPtr<Value>& value) override;
	void search(const MyString& key) const override;
};
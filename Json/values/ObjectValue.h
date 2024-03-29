#pragma once
#include "Value.h"
#include "../data structures/HashMap.hpp"
#include "../PolymorphicPtr.hpp"
#include "../MyString.h"

class ObjectValue : public Value {
	HashMap<MyString, PolymorphicPtr<Value>, hash> map;

	PolymorphicPtr<Value>& getDestFromPath(const MyString& path) override;
	PolymorphicPtr<Value> getOriginFromPath(const MyString& path) override;

	const PolymorphicPtr<Value>& getAt(const MyString& path) const override;

public:
	Value* clone() const override;
	void setValue(const HashMap<MyString, PolymorphicPtr<Value>, hash>& value) override;
	void write(std::ostream& os, size_t indent = 2) const override;
	void writeAt(std::ostream& os, const MyString& path, size_t indent = 2) const;
	void set(const MyString& path, const PolymorphicPtr<Value>& value) override;
	void search(const MyString& key) const override;
	void find(const MyString& key) const override;
	void create(const MyString& path, const PolymorphicPtr<Value>& value) override;
	void deletePath(const MyString& path) override;
	void moveFromTo(const MyString& origin, const MyString& dest) override;

	friend class Json;
	friend class JsonParser;
};
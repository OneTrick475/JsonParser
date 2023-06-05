#pragma once
#include "Value.h"

class VectorValue : public Value {
	Vector<PolymorphicPtr<Value>> vector;
public:
	Value* clone() const override;
	void setValue(const Vector<PolymorphicPtr<Value>>& value) override;
	void write(std::ostream& os, size_t indent) const override;
	void search(const MyString& key) const override;
};


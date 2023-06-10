#pragma once
#include "Value.h"
#include "../MyString.h"

class StringValue : public Value {
	MyString string;
public:
	Value* clone() const override;
	void setValue(const MyString& value) override;
	void write(std::ostream& os, size_t indent) const override;
};

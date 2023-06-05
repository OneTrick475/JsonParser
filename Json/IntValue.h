#pragma once
#include "Value.h"

class IntValue : public Value {
	int _int;
public:
	Value* clone() const override;
	void setValue(int value) override;
	void write(std::ostream& os, size_t indent) const override;
};


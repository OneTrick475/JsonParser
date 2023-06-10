#pragma once
#include "Value.h"

class DoubleValue : public Value {
	double _double;
public:
	Value* clone() const override;
	void setValue(double value) override;
	void write(std::ostream& os, size_t indent) const override;
};

#pragma once
#include "Value.h"

class BoolValue : public Value {
	bool _bool;
public:
	Value* clone() const override;
	void setValue(bool value) override;
	void write(std::ostream& os, size_t indent) const override;
};

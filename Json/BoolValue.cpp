#include "BoolValue.h"

Value* BoolValue::clone() const {
	return new BoolValue(*this);
}

void BoolValue::write(std::ostream& os, size_t indent) const {
	os << _bool;
}

void BoolValue::setValue(bool value) {
	_bool = value;
}


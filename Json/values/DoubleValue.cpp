#include "DoubleValue.h"

Value* DoubleValue::clone() const {
    return new DoubleValue(*this);
}

void DoubleValue::write(std::ostream& os, size_t indent) const {
	os << _double;
}

void DoubleValue::setValue(double value) {
	_double = value;
}


#include "IntValue.h"

Value* IntValue::clone() const {
    return new IntValue(*this);
}

void IntValue::write(std::ostream& os, size_t indent) const {
	os << _int;
}

void IntValue::setValue(int value) {
	_int = value;
}


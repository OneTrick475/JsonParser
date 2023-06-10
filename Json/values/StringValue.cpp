#include "StringValue.h"

Value* StringValue::clone() const {
    return new StringValue(*this);
}

void StringValue::setValue(const MyString& value) {
	string = value;
}

void StringValue::write(std::ostream& os, size_t indent) const {
	os << "\"" << string << "\"";
}



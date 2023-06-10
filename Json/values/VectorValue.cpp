#include "VectorValue.h"

Value* VectorValue::clone() const {
    return new VectorValue(*this);
}

void VectorValue::setValue(const Vector<PolymorphicPtr<Value>>& value) {
	vector = value;
}

void VectorValue::write(std::ostream& os, size_t _indent) const {
	bool isFirst = true;

	os << "[";
	for (size_t i = 0; i < vector.len(); i++) {
		if (!isFirst)
			os << ",";

		os << "\n";
		indent(os, _indent);
		(*vector[i]).write(os, _indent + 2);
		isFirst = false;

	}
	os << "\n";
	indent(os, _indent - 2);
	os << ']';
}

void VectorValue::search(const MyString& key) const {
	if (vector.len() == 0)
		return;

	for (size_t i = 0; i < vector.len(); i++) {
		(*vector[i]).search(key);
	}
}




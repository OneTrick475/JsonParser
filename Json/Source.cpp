#include <iostream>
#include "MyString.h"
#include "Json.h"
#include "UniquePointer.h"

int main() {
	UniquePointer<int> idk(new int(15));
	std::cout << *idk;

	UniquePointer<MyString> str(new MyString("123"));
	std::cout << str->c_str();
};
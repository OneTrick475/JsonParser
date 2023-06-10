#include "CommandFactory.h"
#include <iostream>

#include "ParseCommand.h"
#include "PrintCommand.h"
#include "SetCommand.h"
#include "../MyString.h"

const CommandFactory& CommandFactory::getInstance() {
	static CommandFactory factory;
	return factory;
}

const Command* CommandFactory::create(std::istream& is, Json& json) const {
	size_t option;
	std::cin >> option;

	if(option == 0) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		return new ParseCommand(path, json);
	}
	if (option == 1)
		return new PrintCommand(json);
	if(option == 3) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		MyString value;
		std::cout << "type a json value: ";
		std::cin >> value;
		return new SetCommand(path, value, json);
	}
		
}

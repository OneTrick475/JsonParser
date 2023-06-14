#include "CommandFactory.h"
#include <iostream>
#include "CreateCommand.h"
#include "DeleteCommand.h"
#include "MoveCommand.h"
#include "ParseCommand.h"
#include "PrintCommand.h"
#include "SaveAsCommand.h"
#include "SaveCommand.h"
#include "SearchCommand.h"
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
	if(option == 2) {
		std::cout << "type a key: ";
		MyString path;
		std::cin >> path;
		return new SearchCommand(path, json);
	}
	if(option == 3) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		MyString value;
		std::cout << "type a json value: ";
		std::cin >> value;
		return new SetCommand(path, value, json);
	}
	if (option == 4) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		MyString value;
		std::cout << "type a json value: ";
		std::cin >> value;
		return new CreateCommand(path, value, json);
	}
	if(option == 5) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		return new DeleteCommand(path, json);
	}
	if(option == 6) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;
		MyString path2;
		std::cout << "type a path: ";
		std::cin >> path2;
		return new MoveCommand(path, path2, json);
	}
	if(option == 7) {
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;

		if (path == "\"\"")
			return new SaveCommand("", json);

		return new SaveCommand(path, json);
	}
	if(option == 8) {
		std::cout << "type a file path: ";
		MyString file;
		std::cin >> file;
		std::cout << "type a path: ";
		MyString path;
		std::cin >> path;

		if (path == "\"\"")
			return new SaveAsCommand("\0", file, json);

		return new SaveAsCommand(path, file, json);
	}
	if(option == 9) {
		std::exit(0);
	}
}

#include "JsonCli.h"
#include "Commands/Command.h"
#include "Commands/CommandFactory.h"

void JsonCli::printMenu() const {
	std::cout << "0.Parse \n1. print\n2. search\n3. set\n4. create\n5. delete\n 6. move\n7. save\n8. save as\n9. exit\n";
}

void JsonCli::run() {
	std::cout << "Type the number of the command you want to select\n";
	while(true) {
		printMenu();
		const Command* command = CommandFactory::getInstance().create(std::cin, json);
		try {
			command->execute();
		}catch (std::invalid_argument& ex) {
			std::cout << ex.what() << std::endl;
		}
		delete command;
	}
}

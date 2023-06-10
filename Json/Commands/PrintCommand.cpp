#include "PrintCommand.h"
#include "../Json.h"

PrintCommand::PrintCommand(const Json& json) : json(json) {}

void PrintCommand::execute() const {
	json.print();
}


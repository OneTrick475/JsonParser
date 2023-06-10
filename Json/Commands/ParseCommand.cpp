#include "ParseCommand.h"
#include "../Json.h"

ParseCommand::ParseCommand(const MyString& path, Json& json) : path(path), json(json) {}

void ParseCommand::execute() const {
	json.parse(path);
}

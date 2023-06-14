#include "SaveCommand.h"
#include "../Json.h"

SaveCommand::SaveCommand(const MyString& path, Json& json) : path(path), json(json) {}

void SaveCommand::execute() const {
	json.save(path);
}


#include "DeleteCommand.h"
#include "../Json.h"

DeleteCommand::DeleteCommand(const MyString& path, Json& json) : path(path), json(json) {}

void DeleteCommand::execute() const {
	json.deletePath(path);
}

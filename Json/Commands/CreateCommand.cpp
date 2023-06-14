#include "CreateCommand.h"
#include "../Json.h"

CreateCommand::CreateCommand(const MyString& path, const MyString& value, Json& json) : path(path), value(value), json(json) {}

void CreateCommand::execute() const {
	json.create(path, value);
}

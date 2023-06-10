#include "SetCommand.h"
#include "../Json.h"

SetCommand::SetCommand(const MyString& path, const MyString& value, Json& json) : path(path), value(value), json(json) {}

void SetCommand::execute() const {
	json.set(path, value);
}


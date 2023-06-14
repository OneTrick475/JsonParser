#include "MoveCommand.h"

#include "../Json.h"

MoveCommand::MoveCommand(const MyString& from, const MyString& to, Json& json) : from(from), to(to), json(json) {}

void MoveCommand::execute() const {
	json.moveFromTo(from, to);
}


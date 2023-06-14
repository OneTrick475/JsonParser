#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class MoveCommand : public Command {
	MyString from;
	MyString to;
	Json& json;
public:
	MoveCommand(const MyString& from, const MyString& to, Json& json);

	void execute() const override;
};

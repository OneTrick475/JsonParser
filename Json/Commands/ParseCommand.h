#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class ParseCommand : public Command {
	Json& json;
	MyString path;

public:
	ParseCommand(const MyString& path, Json& json);

	void execute() const override;
};

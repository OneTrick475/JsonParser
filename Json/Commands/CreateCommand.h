#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class CreateCommand : public Command {
	MyString path;
	MyString value;
	Json& json;

public:
	CreateCommand(const MyString& path, const MyString& value, Json& json);

	void execute() const override;
};


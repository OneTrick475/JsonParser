#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class DeleteCommand : public Command {
	MyString path;
	Json& json;

public:
	DeleteCommand(const MyString& path, Json& json);

	void execute() const override;
};

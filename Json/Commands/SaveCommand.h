#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class SaveCommand : public Command {
	MyString path;
	Json& json;
public:
	SaveCommand(const MyString& path, Json& json);

	void execute() const override;
};

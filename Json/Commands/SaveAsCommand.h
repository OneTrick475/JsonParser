#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class SaveAsCommand : public Command {
	MyString path;
	MyString file;
	Json& json;
public:
	SaveAsCommand(const MyString& path, const MyString& file, Json& json);

	void execute() const override;
};

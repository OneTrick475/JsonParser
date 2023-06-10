#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class SetCommand : public Command {
	Json& json;
	MyString path;
	MyString value;

public:
	SetCommand(const MyString& path, const MyString& value, Json& json); 
	void execute() const override;
};

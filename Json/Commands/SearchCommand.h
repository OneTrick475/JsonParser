#pragma once
#include "Command.h"
#include "../MyString.h"

class Json;

class SearchCommand : public Command {
	MyString key;
	Json& json;
public:
	SearchCommand(const MyString& key, Json& json);

	void execute() const override;
};

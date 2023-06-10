#pragma once
#include "Command.h"

class Json;

class PrintCommand : public Command{
	const Json& json;
public:
	PrintCommand(const Json& json);
	void execute() const override;
};

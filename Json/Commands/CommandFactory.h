#pragma once
#include <istream>
#include "Command.h"

class Json;

class CommandFactory {

	CommandFactory() = default;
public:
	CommandFactory(const CommandFactory& other) = delete;
	CommandFactory& operator=(const CommandFactory& other) = delete;

	static const CommandFactory& getInstance();
	const Command* create(std::istream& is, Json& json) const;
};

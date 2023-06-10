#pragma once
#include "Json.h"

class JsonCli {
	Json json;

	void printMenu() const;
public:
	void run();
};

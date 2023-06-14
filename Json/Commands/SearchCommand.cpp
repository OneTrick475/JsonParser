#include "SearchCommand.h"
#include "../Json.h"

SearchCommand::SearchCommand(const MyString& key, Json& json) : key(key), json(json) {}

void SearchCommand::execute() const {
	json.search(key);
}


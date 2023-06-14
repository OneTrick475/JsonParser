#include "SaveAsCommand.h"
#include "../Json.h"

SaveAsCommand::SaveAsCommand(const MyString& path, const MyString& file, Json& json) : path(path), file(file), json(json) {}

void SaveAsCommand::execute() const {
	json.saveAs(file, path);
}

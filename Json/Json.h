#pragma once
#include "data structures/HashMap.hpp"
#include "MyString.h"
#include "values/ObjectValue.h"
#include "values/Value.h"
#include "PolymorphicPtr.hpp"

class Json {
private:
	ObjectValue map;
	MyString currentFile;
	
public:
	Json() = default;
	Json(const MyString& fileName);

	void search(const MyString& key) const;
	void find(const MyString& key) const;
	void set(const MyString& path, const MyString& value);
	void create(const MyString& path, const MyString& value);
	void deletePath(const MyString& path);
	void moveFromTo(const MyString& origin, const MyString& dest);

	void parse(const MyString& fileName);
	void print() const;
	void saveAs(const MyString& filePath = "\0", const MyString& path = "\0") const;
	void save(const MyString& path = "\0") const;

	friend std::ostream& operator<<(std::ostream& os, const Json& json);
};





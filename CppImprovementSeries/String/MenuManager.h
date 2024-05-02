#pragma once

#include "AbstractLevel.h"
#include "String.h"

#include <vector>

namespace Menu {

class MenuManager
{
public:
	MenuManager();
public:
	void run();
private:
	void addString();
	void removeString();
	void printStrings();
	void assignString();
	void moveString();
	void concatenateCreateNew();
	void concatenateAppend();
	void compareEqual();
	void compareGreater();
	void compareSmaller();
	void compareEqualOrGreater();
	void compareEqualOrSmaller();
private:
	void createMenu();
	size_t getStringIdx(const String& message);
	bool isEmptyStorage() const;
private:
	using StringStorage = std::vector<String>;
private:
	AbstractLevelPtr mRoot;
	StringStorage mStrings;
};

}
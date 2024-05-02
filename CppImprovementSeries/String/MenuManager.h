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
private:
	size_t getStringIdx();
	void createMenu();
private:
	using StringStorage = std::vector<String>;
private:
	AbstractLevelPtr mRoot;
	StringStorage mStrings;
};

}
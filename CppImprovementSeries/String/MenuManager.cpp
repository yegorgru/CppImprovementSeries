#include "MenuManager.h"
#include "MenuLevel.h"
#include "ActionLevel.h"

#include <iostream>

namespace Menu {

MenuManager::MenuManager() 
{
	createMenu();
}

void MenuManager::run() {
	auto activeLevel = mRoot;
	while (true) {
		activeLevel = activeLevel->makeAction();
		if (!activeLevel) {
			break;
		}
	}
}

void MenuManager::addString() {
	std::cout << "Enter string: " << std::endl;
	std::string s;
	std::cin >> s;
	mStrings.push_back(String(s));
	std::cout << "Added successfully" << std::endl;
}

void MenuManager::removeString() {
	if (mStrings.size() == 0) {
		std::cout << "Storage is already empty!" << std::endl;
	}
	else {
		auto idx = getStringIdx();
		mStrings.erase(mStrings.begin() + idx);
		std::cout << "Removed successfully" << std::endl;
	}
}

void MenuManager::printStrings() {
	size_t counter = 0;
	for (const auto& str : mStrings) {
		std::cout << counter++ << " " << str << std::endl;
	}
}

size_t MenuManager::getStringIdx() {
	while (true) {
		std::cout << "Enter string index: " << std::endl;
		std::string idxStr;
		if (std::cin.rdbuf()->in_avail() > 0) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin >> idxStr;
		int idx = 0;
		try {
			idx = std::stoi(idxStr);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Not number provided!" << std::endl;
			continue;
		}
		if (idx < 0 || idx >= mStrings.size()) {
			std::cout << "Incorrect index!" << std::endl;
			continue;
		}
		return idx;
	}
}

void MenuManager::createMenu() {
	using namespace Menu;
	int id = 0;
	auto root = std::make_shared<MenuLevel>(' ', "", nullptr);
	auto addString = std::make_shared<ActionLevel>('1', "add new String", root, [this]() { this->addString(); });
	root->addChild(addString);
	auto removeString = std::make_shared<ActionLevel>('2', "remove String", root, [this]() { this->removeString(); });
	root->addChild(removeString);
	auto printStrings = std::make_shared<ActionLevel>('3', "print added strings", root, [this]() { this->printStrings(); });
	root->addChild(printStrings);
	mRoot = root;
}

}
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

void MenuManager::createMenu() {
	using namespace Menu;
	auto root = std::make_shared<MenuLevel>(' ', "", nullptr);

	auto addString = std::make_shared<ActionLevel>('1', "add new String", root, [this]() { this->addString(); });
	root->addChild(addString);
	auto removeString = std::make_shared<ActionLevel>('2', "remove String", root, [this]() { this->removeString(); });
	root->addChild(removeString);
	auto printStrings = std::make_shared<ActionLevel>('3', "print added strings", root, [this]() { this->printStrings(); });
	root->addChild(printStrings);
	auto assignString = std::make_shared<ActionLevel>('4', "assign", root, [this]() { this->assignString(); });
	root->addChild(assignString);
	auto moveString = std::make_shared<ActionLevel>('5', "move", root, [this]() { this->moveString(); });
	root->addChild(moveString);

	auto concatenate = std::make_shared<MenuLevel>('6', "concatenate", root);
	root->addChild(concatenate);
	auto concatenateCreateNew = std::make_shared<ActionLevel>('1', "create new concatenated string", concatenate, [this]() { this->concatenateCreateNew(); });
	concatenate->addChild(concatenateCreateNew);
	auto concatenateAppend = std::make_shared<ActionLevel>('2', "concatenate in place", concatenate, [this]() { this->concatenateAppend(); });
	concatenate->addChild(concatenateAppend);

	auto compare = std::make_shared<MenuLevel>('7', "compare", root);
	root->addChild(compare);
	auto compareEqual = std::make_shared<ActionLevel>('1', "equal", compare, [this]() { this->compareEqual(); });
	compare->addChild(compareEqual);
	auto compareGreater = std::make_shared<ActionLevel>('2', "greater", compare, [this]() { this->compareGreater(); });
	compare->addChild(compareGreater);
	auto compareSmaller = std::make_shared<ActionLevel>('3', "smaller", compare, [this]() { this->compareSmaller(); });
	compare->addChild(compareSmaller);
	auto compareEqualOrGreater = std::make_shared<ActionLevel>('4', "equal or greater", compare, [this]() { this->compareEqualOrGreater(); });
	compare->addChild(compareEqualOrGreater);
	auto compareEqualOrSmaller = std::make_shared<ActionLevel>('5', "equal or smaller", compare, [this]() { this->compareEqualOrSmaller(); });
	compare->addChild(compareEqualOrSmaller);

	mRoot = root;
}

void MenuManager::addString() {
	std::cout << "Enter string: " << std::endl;
	std::string s;
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::getline(std::cin, s);
	mStrings.push_back(String(s));
	std::cout << "Added successfully" << std::endl;
}

void MenuManager::removeString() {
	if (!isEmptyStorage()) {
		auto idx = getStringIdx(String("Enter string index"));
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

void MenuManager::assignString() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index to assign to");
		auto idx2 = getStringIdx("Enter index to assign from");
		mStrings[idx1] = mStrings[idx2];
		std::cout << "Assigned successfully" << std::endl;
	}
}

void MenuManager::moveString() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index to move to");
		auto idx2 = getStringIdx("Enter index to move from");
		mStrings[idx1] = std::move(mStrings[idx2]);
		std::cout << "Moved successfully" << std::endl;
	}
}

void MenuManager::concatenateCreateNew() {
	if(!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		mStrings.push_back(mStrings[idx1] + mStrings[idx2]);
		std::cout << "Concatenated successfully" << std::endl;
	}
}

void MenuManager::concatenateAppend() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		mStrings[idx1] += mStrings[idx2];
		std::cout << "Concatenated successfully" << std::endl;
	}
}

void MenuManager::compareEqual() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		std::cout << std::boolalpha << (mStrings[idx1] == mStrings[idx2]) << std::noboolalpha << std::endl;
	}
}

void MenuManager::compareGreater() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		std::cout << std::boolalpha << (mStrings[idx1] > mStrings[idx2]) << std::noboolalpha << std::endl;
	}
}

void MenuManager::compareSmaller() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		std::cout << std::boolalpha << (mStrings[idx1] < mStrings[idx2]) << std::noboolalpha << std::endl;
	}
}

void MenuManager::compareEqualOrGreater() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		std::cout << std::boolalpha << (mStrings[idx1] >= mStrings[idx2]) << std::noboolalpha << std::endl;
	}
}

void MenuManager::compareEqualOrSmaller() {
	if (!isEmptyStorage()) {
		auto idx1 = getStringIdx("Enter index of left string");
		auto idx2 = getStringIdx("Enter index of right string");
		std::cout << std::boolalpha << (mStrings[idx1] <= mStrings[idx2]) << std::noboolalpha << std::endl;
	}
}

size_t MenuManager::getStringIdx(const String& message) {
	while (true) {
		std::cout << message << ": " << std::endl;
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

bool MenuManager::isEmptyStorage() const {
	if (mStrings.size() == 0) {
		std::cout << "Storage is empty!" << std::endl;
		return true;
	}
	return false;
}

}
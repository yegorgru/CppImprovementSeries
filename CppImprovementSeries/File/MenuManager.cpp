#include "MenuManager.h"
#include "MenuLevel.h"
#include "ActionLevel.h"
#include "MyType.h"

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

	auto baseFile = std::make_shared<MenuLevel>('1', "base file", root);
	root->addChild(baseFile);

	auto openFile = std::make_shared<ActionLevel>('1', "open", baseFile, [this]() { this->open(); });
	baseFile->addChild(openFile);
	auto closeFile = std::make_shared<ActionLevel>('2', "close", baseFile, [this]() { this->close(); });
	baseFile->addChild(closeFile);
	auto seekFile = std::make_shared<ActionLevel>('3', "seek", baseFile, [this]() { this->seek(); });
	baseFile->addChild(seekFile);
	auto getPositionFile = std::make_shared<ActionLevel>('4', "get position", baseFile, [this]() { this->getPosition(); });
	baseFile->addChild(getPositionFile);
	auto getLengthFile = std::make_shared<ActionLevel>('5', "get length", baseFile, [this]() { this->getLength(); });
	baseFile->addChild(getLengthFile);

	auto read = std::make_shared<MenuLevel>('6', "read", baseFile);
	baseFile->addChild(read);
	auto readIntFile = std::make_shared<ActionLevel>('1', "read int", read, [this]() { this->readInt(); });
	read->addChild(readIntFile);
	auto readStringFile = std::make_shared<ActionLevel>('2', "read string", read, [this]() { this->readString(); });
	read->addChild(readStringFile);
	auto readTypeFile = std::make_shared<ActionLevel>('3', "read type", read, [this]() { this->readType(); });
	read->addChild(readTypeFile);

	auto write = std::make_shared<MenuLevel>('7', "write", baseFile);
	baseFile->addChild(write);
	auto writeIntFile = std::make_shared<ActionLevel>('1', "write int", write, [this]() { this->writeInt(); });
	write->addChild(writeIntFile);
	auto writeStringFile = std::make_shared<ActionLevel>('2', "write string", write, [this]() { this->writeString(); });
	write->addChild(writeStringFile);
	auto writeTypeFile = std::make_shared<ActionLevel>('3', "write type", write, [this]() { this->writeType(); });
	write->addChild(writeTypeFile);

	auto typeFile = std::make_shared<MenuLevel>('2', "type file", root);
	root->addChild(typeFile);

	mRoot = root;
}

void MenuManager::open() {
	std::cout << "Enter filename: " << std::endl;
	std::string name;
	std::cin >> name;
	mFile.open(name);
	std::cout << "Open successfully" << std::endl;
}

void MenuManager::close() {
	mFile.close();
	std::cout << "Close successfully" << std::endl;
}

void MenuManager::seek() {
	auto pos = getPositionInput("Enter position");
	try
	{
		mFile.seek(pos);
		std::cout << "Seek successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::getPosition() {
	try
	{
		std::cout << "Position is: " << mFile.getPosition() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::getLength() {
	try
	{
		std::cout << "Length is: " << mFile.getLength() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::readInt() {
	try
	{
		int read;
		mFile.read(read);
		std::cout << "Int: " << read << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::readString() {
	try
	{
		std::string read;
		mFile.read(read);
		std::cout << "String: " << read << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::readType() {
	try
	{
		MyType read;
		mFile.read(read);
		std::cout << "Type: " << read << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::writeInt() {
	try
	{
		auto input = getIntInput("Input int");
		mFile.write(input);
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::writeString() {
	try
	{
		auto input = getStringInput("Input string");
		mFile.write(input);
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void MenuManager::writeType() {
	try
	{
		auto input1 = getDoubleInput("Input x");
		auto input2 = getDoubleInput("Input y");
		auto input3 = getDoubleInput("Input z");
		MyType coords(input1, input2, input3);
		mFile.write(coords);
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

File::PositionType MenuManager::getPositionInput(const std::string& message) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		if (std::cin.rdbuf()->in_avail() > 0) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin >> str;
		int input = 0;
		try {
			input = std::stoi(str);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Not number provided!" << std::endl;
			continue;
		}
		if (input < 0) {
			std::cout << "Incorrect position!" << std::endl;
			continue;
		}
		return input;
	}
}

int MenuManager::getIntInput(const std::string& message) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		if (std::cin.rdbuf()->in_avail() > 0) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin >> str;
		int input = 0;
		try {
			input = std::stoi(str);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Not int provided!" << std::endl;
			continue;
		}
		return input;
	}
}

std::string MenuManager::getStringInput(const std::string& message) {
	std::cout << message << ": " << std::endl;
	std::string str;
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin >> str;
	return str;
}

double MenuManager::getDoubleInput(const std::string& message) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		if (std::cin.rdbuf()->in_avail() > 0) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cin >> str;
		double input = 0;
		try {
			input = std::stod(str);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Not double provided!" << std::endl;
			continue;
		}
		return input;
	}
}

}
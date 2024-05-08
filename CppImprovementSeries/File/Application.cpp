#include "Application.h"
#include "MenuLevel.h"
#include "ActionLevel.h"

#include <iostream>

Application::Application()
{
	createMenu();
}

void Application::run() {
	auto activeLevel = mRoot;
	while (true) {
		activeLevel = activeLevel->makeAction();
		if (!activeLevel) {
			break;
		}
	}
}

void Application::createMenu() {
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
	auto readDoubleFile = std::make_shared<ActionLevel>('3', "read double", read, [this]() { this->readDouble(); });
	read->addChild(readDoubleFile);

	auto write = std::make_shared<MenuLevel>('7', "write", baseFile);
	baseFile->addChild(write);
	auto writeIntFile = std::make_shared<ActionLevel>('1', "write int", write, [this]() { this->writeInt(); });
	write->addChild(writeIntFile);
	auto writeStringFile = std::make_shared<ActionLevel>('2', "write string", write, [this]() { this->writeString(); });
	write->addChild(writeStringFile);
	auto writeDoubleFile = std::make_shared<ActionLevel>('3', "write double", write, [this]() { this->writeDouble(); });
	write->addChild(writeDoubleFile);

	auto dataFile = std::make_shared<MenuLevel>('2', "data file", root);
	root->addChild(dataFile);

	auto openDataFile = std::make_shared<ActionLevel>('1', "open", dataFile, [this]() { this->openData(); });
	dataFile->addChild(openDataFile);
	auto closeDataFile = std::make_shared<ActionLevel>('2', "close", dataFile, [this]() { this->closeData(); });
	dataFile->addChild(closeDataFile);
	auto readDataFile = std::make_shared<ActionLevel>('3', "read data", dataFile, [this]() { this->readData(); });
	dataFile->addChild(readDataFile);
	auto writeDataFile = std::make_shared<ActionLevel>('4', "write data", dataFile, [this]() { this->writeData(); });
	dataFile->addChild(writeDataFile);
	auto getCountDataFile = std::make_shared<ActionLevel>('5', "get data count", dataFile, [this]() { this->getCountData(); });
	dataFile->addChild(getCountDataFile);

	mRoot = root;
}

void Application::open() {
	std::string name;
	while (true) {
		std::cout << "Enter filename: " << std::endl;
		getStringLine(name);
		if (name.length() == 0) {
			std::cout << "Filename can't be empty!" << std::endl;
		}
		else {
			break;
		}
	}
	try
	{
		mFile.open(name);
		std::cout << "Open successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::close() {
	mFile.close();
	std::cout << "Close successfully" << std::endl;
}

void Application::seek() {
	auto pos = getIntInput("Enter position", true);
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

void Application::getPosition() {
	try
	{
		auto pos = mFile.getPosition();
		std::cout << "Position is: " << pos << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::getLength() {
	try
	{
		auto length = mFile.getLength();
		std::cout << "Length is: " << length << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::readInt() {
	try
	{
		int number;
		mFile.read(reinterpret_cast<char*>(&number), sizeof(number));
		std::cout << "Int: " << number << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::readString() {
	try
	{
		auto count = getIntInput("Enter characters count", true);
		std::string str(count, ' ');
		mFile.read(str.data(), count);
		std::cout << "String: " << str << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::readDouble() {
	try
	{
		double d;
		mFile.read(reinterpret_cast<char*>(&d), sizeof(d));
		std::cout << "Double: " << d << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::writeInt() {
	try
	{
		auto input = getIntInput("Input int", false);
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::writeString() {
	try
	{
		auto input = getStringInput("Input string");
		mFile.write(input.data(), input.size());
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::writeDouble() {
	try
	{
		auto input = getDoubleInput("Input double");
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::openData() {
	std::string name;
	while (true) {
		std::cout << "Enter filename: " << std::endl;
		getStringLine(name);
		if (name.length() == 0) {
			std::cout << "Filename can't be empty!" << std::endl;
		}
		else {
			break;
		}
	}
	try
	{
		mDataFile.open(name);
		std::cout << "Open successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::closeData() {
	mDataFile.close();
	std::cout << "Close successfully" << std::endl;
}

void Application::readData() {
	try
	{
		DataFile::Data data;
		auto idx = getIntInput("Input index", true);
		mDataFile.read(data, idx);
		std::cout << "a: " << data.a <<
			", b: " << data.b <<
			", c: " << data.c <<
			", name: " << data.name.data() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::writeData() {
	try
	{
		auto data = getDataInput("Input data struct");
		auto idx = getIntInput("Input index", true);
		mDataFile.write(data, idx);
		std::cout << "Write successfully" << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

void Application::getCountData() {
	try
	{
		auto length = mDataFile.getDataCount();
		std::cout << "Data count is: " << length << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error happened: " << ex.what() << std::endl;
	}
}

int Application::getIntInput(const std::string& message, bool positiveCheck) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		getStringLine(str);
		int input = 0;
		try {
			input = std::stoi(str);
		}
		catch (std::invalid_argument& ex) {
			std::cout << "Not integer provided!" << std::endl;
			continue;
		}
		if (positiveCheck && input < 0) {
			std::cout << "Value should be greater or equal to 0!" << std::endl;
			continue;
		}
		return input;
	}
}

std::string Application::getStringInput(const std::string& message, size_t maxSize) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		getStringLine(str);
		if (str.length() > maxSize) {
			std::cout << "String is too long!" << std::endl;
			continue;
		}
		return str;
	}
}

double Application::getDoubleInput(const std::string& message) {
	while (true) {
		std::cout << message << ": " << std::endl;
		std::string str;
		getStringLine(str);
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

void Application::getStringLine(std::string& str) {
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::getline(std::cin, str);
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

DataFile::Data Application::getDataInput(const std::string& message) {
	std::cout << message << ": " << std::endl;
	DataFile::Data data;
	auto name = getStringInput("Input name (<=5 characters)", 5);
	std::strcpy(data.name.data(), name.c_str());
	data.name.back() = '\0';
	data.a = getIntInput("Input a", true);
	data.b = getIntInput("Input b", true);
	data.c = getIntInput("Input c", true);
	return data;
}
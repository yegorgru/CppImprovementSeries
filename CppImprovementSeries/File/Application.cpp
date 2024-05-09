#include "Application.h"
#include "MenuLevel.h"
#include "ActionLevel.h"

Application::Application()
{
	mView.setMenuRoot(createMenu());
}

void Application::run() {
	while (true) {
		auto actionCode = mView.runMenuItem();
		switch (actionCode) {
		case ActionCode::OpenFile:
			open();
			break;
		case ActionCode::CloseFile:
			close();
			break;
		case ActionCode::SeekFile:
			seek();
			break;
		case ActionCode::GetPositionFile:
			getPosition();
			break;
		case ActionCode::GetLengthFile:
			getLength();
			break;
		case ActionCode::ReadIntFile:
			readInt();
			break;
		case ActionCode::ReadStringFile:
			readString();
			break;
		case ActionCode::ReadDoubleFile:
			readDouble();
			break;
		case ActionCode::WriteIntFile:
			writeInt();
			break;
		case ActionCode::WriteStringFile:
			writeString();
			break;
		case ActionCode::WriteDoubleFile:
			writeDouble();
			break;
		case ActionCode::OpenDataFile:
			openData();
			break;
		case ActionCode::CloseDataFile:
			closeData();
			break;
		case ActionCode::ReadDataFile:
			readData();
			break;
		case ActionCode::WriteDataFile:
			writeData();
			break;
		case ActionCode::GetCountDataFile:
			getCountData();
			break;
		case ActionCode::Exit:
			return;
		case ActionCode::None:
		default:
			break;
		}
	}
}

View::MenuItemPtr Application::createMenu() {
	using namespace Menu;
	using MenuLevel = MenuLevel<ActionCode>;
	using ActionLevel = ActionLevel<ActionCode>;

	auto root = std::make_shared<MenuLevel>(' ', "", nullptr, ActionCode::None);

	auto baseFile = std::make_shared<MenuLevel>('1', "base file", root, ActionCode::None);
	root->addChild(baseFile);

	auto openFile = std::make_shared<ActionLevel>('1', "open", baseFile, ActionCode::OpenFile);
	baseFile->addChild(openFile);
	auto closeFile = std::make_shared<ActionLevel>('2', "close", baseFile, ActionCode::CloseFile);
	baseFile->addChild(closeFile);
	auto seekFile = std::make_shared<ActionLevel>('3', "seek", baseFile, ActionCode::SeekFile);
	baseFile->addChild(seekFile);
	auto getPositionFile = std::make_shared<ActionLevel>('4', "get position", baseFile, ActionCode::GetPositionFile);
	baseFile->addChild(getPositionFile);
	auto getLengthFile = std::make_shared<ActionLevel>('5', "get length", baseFile, ActionCode::GetLengthFile);
	baseFile->addChild(getLengthFile);

	auto read = std::make_shared<MenuLevel>('6', "read", baseFile, ActionCode::None);
	baseFile->addChild(read);
	auto readIntFile = std::make_shared<ActionLevel>('1', "read int", read, ActionCode::ReadIntFile);
	read->addChild(readIntFile);
	auto readStringFile = std::make_shared<ActionLevel>('2', "read string", read, ActionCode::ReadStringFile);
	read->addChild(readStringFile);
	auto readDoubleFile = std::make_shared<ActionLevel>('3', "read double", read, ActionCode::ReadDoubleFile);
	read->addChild(readDoubleFile);

	auto write = std::make_shared<MenuLevel>('7', "write", baseFile, ActionCode::None);
	baseFile->addChild(write);
	auto writeIntFile = std::make_shared<ActionLevel>('1', "write int", write, ActionCode::WriteIntFile);
	write->addChild(writeIntFile);
	auto writeStringFile = std::make_shared<ActionLevel>('2', "write string", write, ActionCode::WriteStringFile);
	write->addChild(writeStringFile);
	auto writeDoubleFile = std::make_shared<ActionLevel>('3', "write double", write, ActionCode::WriteDoubleFile);
	write->addChild(writeDoubleFile);

	auto dataFile = std::make_shared<MenuLevel>('2', "data file", root, ActionCode::None);
	root->addChild(dataFile);

	auto openDataFile = std::make_shared<ActionLevel>('1', "open", dataFile, ActionCode::OpenDataFile);
	dataFile->addChild(openDataFile);
	auto closeDataFile = std::make_shared<ActionLevel>('2', "close", dataFile, ActionCode::CloseDataFile);
	dataFile->addChild(closeDataFile);
	auto readDataFile = std::make_shared<ActionLevel>('3', "read data", dataFile, ActionCode::ReadDataFile);
	dataFile->addChild(readDataFile);
	auto writeDataFile = std::make_shared<ActionLevel>('4', "write data", dataFile, ActionCode::WriteDataFile);
	dataFile->addChild(writeDataFile);
	auto getCountDataFile = std::make_shared<ActionLevel>('5', "get data count", dataFile, ActionCode::GetCountDataFile);
	dataFile->addChild(getCountDataFile);

	return root;
}

void Application::open() {
	std::string name;
	while (true) {
		mView.showMessage("Enter filename: ");
		name = mView.getStringLine();
		if (name.length() == 0) {
			mView.showErrorMessage("Filename can't be empty!");
		}
		else {
			break;
		}
	}
	try
	{
		mFile.open(name);
		mView.showMessage("Open successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::close() {
	mFile.close();
	mView.showMessage("Close successfully");
}

void Application::seek() {
	auto pos = getInt("Enter position", true);
	try
	{
		mFile.seek(pos);
		mView.showMessage("Seek successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::getPosition() {
	try
	{
		auto pos = mFile.getPosition();
		mView.showMessage("Position is: ", pos);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::getLength() {
	try
	{
		auto length = mFile.getLength();
		mView.showMessage("Length is: ", length);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::readInt() {
	try
	{
		int number;
		mFile.read(reinterpret_cast<char*>(&number), sizeof(number));
		mView.showMessage("Int: ", number);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::readString() {
	try
	{
		auto count = getInt("Enter characters count", true);
		std::string str(count, ' ');
		mFile.read(str.data(), count);
		mView.showMessage("String: ", str);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::readDouble() {
	try
	{
		double d;
		mFile.read(reinterpret_cast<char*>(&d), sizeof(d));
		mView.showMessage("Double: ", d);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::writeInt() {
	try
	{
		auto input = getInt("Input int", false);
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		mView.showMessage("Write successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::writeString() {
	try
	{
		auto input = getString("Input string");
		mFile.write(input.data(), input.size());
		mView.showMessage("Write successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::writeDouble() {
	try
	{
		auto input = getDouble("Input double");
		mFile.write(reinterpret_cast<char*>(&input), sizeof(input));
		mView.showMessage("Write successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage("Error happened: ", ex.what());
	}
}

void Application::openData() {
	std::string name;
	while (true) {
		mView.showMessage("Enter filename: ");
		name = mView.getStringLine();
		if (name.length() == 0) {
			mView.showErrorMessage("Filename can't be empty!");
		}
		else {
			break;
		}
	}
	try
	{
		mDataFile.open(name);
		mView.showMessage("Open successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage(std::string("Error happened: ") + ex.what());
	}
}

void Application::closeData() {
	mDataFile.close();
	mView.showMessage("Close successfully");
}

void Application::readData() {
	try
	{
		DataFile::Data data;
		auto idx = getInt("Input index", true);
		mDataFile.read(data, idx);
		mView.showMessage("a: ", data.a, ", b: ", data.b, ", c: ", data.c, ", name: ", data.name.data());
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage(std::string("Error happened: ") + ex.what());
	}
}

void Application::writeData() {
	try
	{
		auto data = getData("Input data struct");
		auto idx = getInt("Input index", true);
		mDataFile.write(data, idx);
		mView.showMessage("Write successfully");
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage(std::string("Error happened: ") + ex.what());
	}
}

void Application::getCountData() {
	try
	{
		auto length = mDataFile.getDataCount();
		mView.showMessage("Data count is: ", length);
	}
	catch (const std::exception& ex)
	{
		mView.showErrorMessage(std::string("Error happened: ") + ex.what());
	}
}

int Application::getInt(const std::string& message, bool positiveCheck) {
	while (true) {
		mView.showMessage(message, ": ");
		std::string str = mView.getStringLine();
		int input = 0;
		try {
			input = std::stoi(str);
		}
		catch (std::invalid_argument& ex) {
			mView.showErrorMessage("Not integer provided!");
			continue;
		}
		if (positiveCheck && input < 0) {
			mView.showErrorMessage("Value should be greater or equal to 0!");
			continue;
		}
		return input;
	}
}

std::string Application::getString(const std::string& message, size_t maxSize) {
	while (true) {
		mView.showMessage(message, ": ");
		std::string str = mView.getStringLine();
		if (str.length() > maxSize) {
			mView.showErrorMessage("String is too long!");
			continue;
		}
		return str;
	}
}

double Application::getDouble(const std::string& message) {
	while (true) {
		mView.showMessage(message, ": ");
		std::string str = mView.getStringLine();
		double input = 0;
		try {
			input = std::stod(str);
		}
		catch (std::invalid_argument& ex) {
			mView.showErrorMessage("Not double provided!");
			continue;
		}
		return input;
	}
}

DataFile::Data Application::getData(const std::string& message) {
	mView.showMessage(message, ": ");
	DataFile::Data data;
	auto name = getString("Input name (<=5 characters)", 5);
	std::strcpy(data.name.data(), name.c_str());
	data.name.back() = '\0';
	data.a = getInt("Input a", true);
	data.b = getInt("Input b", true);
	data.c = getInt("Input c", true);
	return data;
}
#pragma once

#include "AbstractLevel.h"
#include "File.h"
#include "DataFile.h"

class Application
{
public:
	Application();
public:
	void run();
private:
	void open();
	void close();
	void seek();
	void readInt();
	void readString();
	void readDouble();
	void writeInt();
	void writeString();
	void writeDouble();
	void getPosition();
	void getLength();
private:
	void openData();
	void closeData();
	void readData();
	void writeData();
	void getCountData();
private:
	void createMenu();
	int getIntInput(const std::string& message, bool positiveCheck);
	std::string getStringInput(const std::string& message, size_t maxSize = SIZE_MAX);
	double getDoubleInput(const std::string& message);
	void getStringLine(std::string& str);
	DataFile::Data getDataInput(const std::string& message);
private:
	Menu::AbstractLevelPtr mRoot;
	File mFile;
	DataFile mDataFile;
};
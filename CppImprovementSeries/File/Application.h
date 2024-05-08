#pragma once

#include "AbstractLevel.h"
#include "File.h"

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
	void createMenu();
	int getIntInput(const std::string& message, bool positiveCheck);
	std::string getStringInput(const std::string& message);
	double getDoubleInput(const std::string& message);
	void getStringLine(std::string& str);
private:
	Menu::AbstractLevelPtr mRoot;
	File mFile;
};
#pragma once

#include "AbstractLevel.h"
#include "File.h"
#include "DataFile.h"
#include "View.h"

class Application
{
public:
	Application();
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = default;
	Application& operator=(Application&& other) = default;
	~Application() = default;
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
	View::MenuItemPtr createMenu();
	int getInt(const std::string& message, bool positiveCheck);
	std::string getString(const std::string& message, size_t maxSize = SIZE_MAX);
	double getDouble(const std::string& message);
	DataFile::Data getData(const std::string& message);
private:
	View mView;
	File mFile;
	DataFile mDataFile;
};
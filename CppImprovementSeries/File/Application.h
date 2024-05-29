#pragma once

#include "File.h"
#include "DataFile.h"
#include "View.h"

class Application
{
public:
	class Messages {
	public:
		inline static const std::string EnterFilename = "Enter filename";
		inline static const std::string OpenSuccess = "Open successfully";
		inline static const std::string CloseSuccess = "Close successfully";
		inline static const std::string EnterPosition = "Enter position";
		inline static const std::string SeekSuccess = "Seek successfully";
		inline static const std::string EnterCharactersCount = "Enter characters count";
		inline static const std::string WriteSuccess = "Write successfully";
		inline static const std::string AppendSuccess = "Append successfully";
		inline static const std::string InputInt = "Input int";
		inline static const std::string InputString = "Input string";
		inline static const std::string InputDouble = "Input double";
		inline static const std::string InputIndex = "Input index";
		inline static const std::string InputDataStruct = "Input data struct in format name a b c";
		inline static const std::string Exit = "Exiting";
		inline static const std::string TooLongName = "Too long name provided. Resized to 5 characters";
	};

	class ErrorMessages {
	public:
		inline static const std::string ErrorHappened = "Error happened: ";
		inline static const std::string UnsupportedMenuKey = "Unsupported menu key";
		inline static const std::string NotNegativeValue = "Value should be greater or equal to 0!";
		inline static const std::string IncorrectDataInput = "Incorrect data input";
		inline static const std::string IncorrectIntInput = "Incorrect int input";
		inline static const std::string IncorrectDoubleInput = "Incorrect double input";
	};
public:
	Application() = default;
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = default;
	Application& operator=(Application&& other) = default;
	~Application() = default;
public:
	void run();
private:
	int getInt(const std::string& message, bool positiveCheck);
	double getDouble(const std::string& message);
	DataFile::Data getData(const std::string& message);
private:
	View mView;
	File mFile;
	DataFile mDataFile;
};
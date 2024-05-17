#pragma once

#include "File.h"
#include "DataFile.h"
#include "View.h"

class Application
{
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
private:
	class Messages {
	public:
		inline static std::string EnterFilename = "Enter filename";
		inline static std::string OpenSuccess = "Open successfully";
		inline static std::string CloseSuccess = "Close successfully";
		inline static std::string EnterPosition = "Enter position";
		inline static std::string SeekSuccess = "Seek successfully";
		inline static std::string EnterCharactersCount = "Enter characters count";
		inline static std::string WriteSuccess = "Write successfully";
		inline static std::string AppendSuccess = "Append successfully";
		inline static std::string InputInt = "Input int";
		inline static std::string InputString = "Input string";
		inline static std::string InputDouble = "Input double";
		inline static std::string InputIndex = "Input index";
		inline static std::string InputDataStruct = "Input data struct in format name a b c";
		inline static std::string Exit = "Exiting";
		inline static std::string TooLongName = "Too long name provided. Resized to 5 characters";
	};
	
	class ErrorMessages {
	public:
		inline static std::string ErrorHappened = "Error happened: ";
		inline static std::string UnsupportedMenuKey = "Unsupported menu key";
		inline static std::string NotNegativeValue = "Value should be greater or equal to 0!";
		inline static std::string IncorrectDataInput = "Incorrect data input";
		inline static std::string IncorrectIntInput = "Incorrect int input";
		inline static std::string IncorrectDoubleInput = "Incorrect double input";
	};
};
#pragma once

#include <stdexcept>
#include <string>

class Exception : std::exception
{
public:
	Exception(const std::string& message = "");
public:
	const char* what() const override;
protected:
	std::string mMessage;
};

class InputException : public Exception
{
public:
	InputException(const std::string& message = "", bool addTitle = true);
private:
	inline static const std::string mTitle = "Input Exception | ";
};

class FileException : public Exception
{
public:
	FileException(const std::string& message = "", bool addTitle = true);
private:
	inline static const std::string mTitle = "File Exception | ";
};

class DataFileException : public FileException
{
public:
	DataFileException(const std::string& message = "", bool addTitle = true);
private:
	inline static const std::string mTitle = "Data File Exception | ";
};
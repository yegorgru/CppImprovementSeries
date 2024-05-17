#include "Exception.h"

Exception::Exception(const std::string& message) 
	: mMessage(message)
{
}
	
const char* Exception::what() const {
	return mMessage.c_str();
}

InputException::InputException(const std::string& message, bool addTitle)
	: Exception((addTitle ? mTitle : std::string("")) + message)
{
}

FileException::FileException(const std::string& message, bool addTitle)
	: Exception((addTitle ? mTitle : std::string("")) + message)
{
}

DataFileException::DataFileException(const std::string& message, bool addTitle)
	: FileException((addTitle ? mTitle : std::string("")) + message, false)
{
}
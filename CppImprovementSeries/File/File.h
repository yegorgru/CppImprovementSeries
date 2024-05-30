#pragma once

#include "Mode.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

class File;
using FilePtr = std::unique_ptr<File>;

class File
{
public:
	using PositionType = std::ios::pos_type;
public:
	class ErrorMessages {
	public:
		inline static const std::string FileNotOpen = "File is not open";
		inline static const std::string ReadOutOfBounds = "Trying to read data out of file bounds";
		inline static const std::string FileAlreadyExists = "File already exists";
		inline static const std::string FileDoesntExists = "File doesn't exist";
	};
public:
	File() = default;
    explicit File(const std::string& filename, Mode mode = Mode::Open);
	File(const File& other) = delete;
	File& operator=(const File& other) = delete;
	File(File&& other) = default;
	File& operator=(File&& other) = default;
	virtual ~File() = default;
public:
	virtual void open(const std::string& filename, Mode mode = Mode::Open);
	virtual void close();
	void seek(PositionType pos);
	virtual void read(char* buff, std::streamsize count);
	virtual void write(const char* data, std::streamsize count);
	PositionType getPosition();
	PositionType getLength();
public:
	File& operator<<(int value);
	File& operator<<(double value);
	File& operator<<(const std::string& value);
	File& operator>>(int& value);
	File& operator>>(double& value);
	File& operator>>(std::string& value);
protected:
	void checkOpen() const;
protected:
    std::fstream mFile;
};
#pragma once

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
	File() = default;
    explicit File(const std::string& filename);
	File(const File& other) = delete;
	File& operator=(const File& other) = delete;
	File(File&& other) = default;
	File& operator=(File&& other) = default;
	virtual ~File() = default;
public:
	virtual void open(const std::string& filename);
	virtual void close();
	void seek(PositionType pos);
	void read(char* buff, std::streamsize count);
	void write(const char* data, std::streamsize count);
	PositionType getPosition();
	PositionType getLength();
protected:
	void checkOpen();
protected:
	std::string mFilename;
    std::fstream mFile;
};
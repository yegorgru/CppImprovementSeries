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
	virtual void read(char* buff, std::streamsize count);
	virtual void write(const char* data, std::streamsize count);
	PositionType getPosition();
	PositionType getLength();
protected:
	void checkOpen();
	virtual void createFile();
protected:
	std::string mFilename;
    std::fstream mFile;
};
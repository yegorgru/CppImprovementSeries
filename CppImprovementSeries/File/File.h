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
	enum class Mode {
		Open,
		Trunc
	};
public:
	File() = default;
    explicit File(const std::string& filename, Mode mode);
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
protected:
	void checkOpen();
protected:
	std::string mFilename;
    std::fstream mFile;
	class ErrorMessages {
	public:
		inline static std::string EmptyFilename = "Filename is empty";
		inline static std::string OpenFailed = "Failed to open file";
		inline static std::string FileNotOpen = "File is not open";
		inline static std::string ReadOutOfBounds = "Trying to read data out of file bounds";
	};
};
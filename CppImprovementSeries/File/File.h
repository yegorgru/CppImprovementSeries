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
	~File() = default;
public:
	void open(const std::string& filename);
	void close();
	void seek(PositionType pos);
	template <typename T>
	void read(T& t);
	template <typename T>
	void write(const T& t);
	PositionType getPosition();
	PositionType getLength();
private:
	void checkOpen();
private:
    std::fstream mFile;
};

template <typename T>
void File::read(T& t) {
	checkOpen();
	mFile >> t;
}

template <typename T>
void File::write(const T& t) {
	checkOpen();
	mFile << t;
	mFile.flush();
}
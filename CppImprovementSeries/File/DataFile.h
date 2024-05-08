#pragma once

#include "File.h"

#include <array>

class DataFile : public File
{
public:
	struct Data {
		std::array<char, 6> name;
		size_t a = 0;
		size_t b = 0;
		size_t c = 0;
	};
public:
	DataFile() = default;
	explicit DataFile(const std::string& filename);
	DataFile(const DataFile& other) = delete;
	DataFile& operator=(const DataFile& other) = delete;
	DataFile(DataFile&& other) = default;
	DataFile& operator=(DataFile&& other) = default;
	virtual ~DataFile() = default;
public:
	void open(const std::string& filename) override;
	void close() override;
	void read(Data& data, size_t idx);
	void write(const Data& data, size_t idx);
	size_t getDataCount();
protected:
	void createFile() override;
	PositionType getHeaderSize();
protected:
	using File::read;
	using File::write;
protected:
	inline static const std::string mFileMarker = "DATAFILE";
	size_t mDataCount = 0;
	size_t mDataStart = 0;
};


#pragma once

#include "File.h"

#include <array>

class DataFile : public File
{
public:
	struct Data {
		static constexpr std::size_t NameSize = 5;
		std::array<char, NameSize + 1> name;
		size_t a = 0;
		size_t b = 0;
		size_t c = 0;
	};
public:
	DataFile() = default;
	explicit DataFile(const std::string& filename, Mode mode = Mode::Open);
	DataFile(const DataFile& other) = delete;
	DataFile& operator=(const DataFile& other) = delete;
	DataFile(DataFile&& other) = default;
	DataFile& operator=(DataFile&& other) = default;
	virtual ~DataFile() = default;
public:
	void open(const std::string& filename, Mode mode) override;
	void read(Data& data, size_t idx);
	void write(const Data& data, size_t idx, bool checkIndex = true);
	void append(const Data& data);
	size_t getDataCount();
protected:
	PositionType getHeaderSize();
protected:
	using File::read;
	using File::write;
protected:
	inline static const std::string mFileMarker = "DATAFILE";
	size_t mDataCount = 0;
	size_t mDataStart = 0;
	class ErrorMessages {
	public:
		inline static std::string IdxOutOfRange = "Idx is out of range";
		inline static std::string FileNotConsistent = "File is not consistent";
	};
};


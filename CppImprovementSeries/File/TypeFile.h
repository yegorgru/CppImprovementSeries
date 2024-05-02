#pragma once

#include "File.h"

#include <vector>

class TypeFile;
using TypeFilePtr = std::unique_ptr<TypeFile>;

class TypeFile : public File
{
public:
	friend class AbstractPrintable;
public:
	TypeFile() = default;
	explicit TypeFile(const std::string& filename);
	TypeFile(const TypeFile& other) = delete;
	TypeFile& operator=(const TypeFile& other) = delete;
	TypeFile(TypeFile&& other) = default;
	TypeFile& operator=(TypeFile&& other) = default;
	~TypeFile() = default;
public:
	void open(const std::string& filename) override;
	void close() override;
	PositionType getFieldShift(size_t pos);
	void writeMetadata(const std::string& metadata);
	void reloadMetadata();
private:
	using FieldShifts = std::vector<PositionType>;
private:
	FieldShifts mFieldShifts;
	File mMetadataFile;
};


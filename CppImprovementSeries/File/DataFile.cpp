#include "DataFile.h"
#include <iostream>

DataFile::DataFile(const std::string& filename)
	: mDataCount(0)
	, mDataStart(0)
{
	open(filename);
}

void DataFile::open(const std::string& filename) {
	File::open(filename);
	File::seek(0);
	bool isInconsistent = false;
	auto headerSize = getHeaderSize();
	if (File::getLength() < headerSize) {
		isInconsistent = true;
	}
	else {
		std::string fileMarker(mFileMarker.length(), ' ');
		File::read(fileMarker.data(), fileMarker.size());
		if (fileMarker != mFileMarker) {
			isInconsistent = true;
		}
		else {
			File::read(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
			File::read(reinterpret_cast<char*>(&mDataStart), sizeof(mDataStart));
			if (mDataStart != File::getPosition() || File::getLength() != mDataCount * sizeof(Data) + headerSize) {
				isInconsistent = true;
			}
		}
	}
	if (isInconsistent) {
		close();
		throw std::runtime_error("File is not consistent");
	}
}

void DataFile::close() {
	File::close();
	mDataCount = 0;
	mDataStart = 0;
}

void DataFile::read(Data& data, size_t idx) {
	checkOpen();
	if (idx >= mDataCount) {
		throw std::out_of_range("Idx is out of range");
	}
	File::seek(idx * sizeof(data) + getHeaderSize());
	File::read(reinterpret_cast<char*>(&data), sizeof(data));
}

void DataFile::write(const Data& data, size_t idx) {
	checkOpen();
	File::seek(idx * sizeof(data) + getHeaderSize());
	File::write(reinterpret_cast<const char*>(&data), sizeof(data));
	if (idx >= mDataCount) {
		mDataCount = idx + 1;
		File::seek(mFileMarker.size());
		File::write(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
	}
}

size_t DataFile::getDataCount() {
	checkOpen();
	return mDataCount;
}

void DataFile::createFile() {
	File::createFile();
	File::write(mFileMarker.data(), mFileMarker.size());
	mDataCount = 0;
	File::write(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
	mDataStart = File::getPosition();
	mDataStart += sizeof(mDataStart);
	File::write(reinterpret_cast<char*>(&mDataStart), sizeof(mDataStart));
}

File::PositionType DataFile::getHeaderSize() {
	return mFileMarker.length() + sizeof(mDataCount) + sizeof(mDataStart);
}
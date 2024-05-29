#include "DataFile.h"
#include "Exception.h"

DataFile::DataFile(const std::string& filename, Mode mode)
	: mDataCount(0)
	, mDataStart(0)
{
	open(filename, mode);
}

void DataFile::open(const std::string& filename, Mode mode) {
	if (mFile.is_open()) {
		close();
	}
	File::open(filename, mode);
	File::seek(0);
	if (hasMode(mode, Mode::Trunc) || hasMode(mode, Mode::Create)) {
		File::write(mFileMarker.data(), mFileMarker.size());
		mDataCount = 0;
		File::write(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
		mDataStart = File::getPosition();
		mDataStart += sizeof(mDataStart);
		File::write(reinterpret_cast<char*>(&mDataStart), sizeof(mDataStart));
	}
	else if (hasMode(mode, Mode::Open) || hasMode(mode, Mode::Ate)) {
		auto headerSize = getHeaderSize();
		if (File::getLength() < headerSize) {
			close();
			throw DataFileException(ErrorMessages::FileNotConsistent);
		}
		std::string fileMarker(mFileMarker.length(), ' ');
		File::read(fileMarker.data(), fileMarker.size());
		if (fileMarker != mFileMarker) {
			close();
			throw DataFileException(ErrorMessages::FileNotConsistent);
		}
		File::read(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
		File::read(reinterpret_cast<char*>(&mDataStart), sizeof(mDataStart));
		if (mDataStart != File::getPosition() || File::getLength() != mDataCount * sizeof(Data) + headerSize) {
			close();
			throw DataFileException(ErrorMessages::FileNotConsistent);
		}
	}
}

void DataFile::read(Data& data, size_t idx) {
	checkOpen();
	if (idx >= mDataCount) {
		throw DataFileException(ErrorMessages::IdxOutOfRange);
	}
	File::seek(idx * sizeof(data) + getHeaderSize());
	File::read(reinterpret_cast<char*>(&data), sizeof(data));
}

void DataFile::write(const Data& data, size_t idx, bool checkIndex) {
	checkOpen();
	if (checkIndex && idx >= mDataCount) {
		throw DataFileException(ErrorMessages::IdxOutOfRange);
	}
	File::seek(idx * sizeof(data) + getHeaderSize());
	File::write(reinterpret_cast<const char*>(&data), sizeof(data));
	if (idx >= mDataCount) {
		mDataCount = idx + 1;
		File::seek(mFileMarker.size());
		File::write(reinterpret_cast<char*>(&mDataCount), sizeof(mDataCount));
	}
}

void DataFile::append(const Data& data) {
	checkOpen();
	write(data, mDataCount, false);
}

size_t DataFile::getDataCount() const {
	checkOpen();
	return mDataCount;
}

File::PositionType DataFile::getHeaderSize() const {
	return mFileMarker.length() + sizeof(mDataCount) + sizeof(mDataStart);
}
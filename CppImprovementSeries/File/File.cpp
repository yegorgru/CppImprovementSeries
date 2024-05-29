#include "File.h"
#include "Exception.h"

#include <filesystem>

File::File(const std::string& filename, Mode mode)
{
	open(filename, mode);
}

void File::open(const std::string& filename, Mode mode) {
	if (mFile.is_open()) {
		close();
	}

	bool fileExisted = std::filesystem::exists(filename);

	auto stdMode = std::ios_base::in | std::ios_base::out;
	if (hasMode(mode, Mode::Trunc)) {
		if (!fileExisted) {
			throw FileException(ErrorMessages::FileDoesntExists);
		}
		stdMode |= std::ios_base::trunc;
	}
	else if (hasMode(mode, Mode::Create)) {
		if (fileExisted) {
			throw FileException(ErrorMessages::FileAlreadyExists);
		}
		stdMode |= std::ios_base::trunc;
	}
	if (hasMode(mode, Mode::Ate)) {
		stdMode |= std::ios_base::ate;
	}
	if (hasMode(mode, Mode::Binary)) {
		stdMode |= std::ios_base::binary;
	}
	mFile.open(filename, stdMode);
	checkOpen();
}

void File::close() {
	mFile.close();
}

void File::seek(PositionType pos) {
	checkOpen();
	mFile.seekp(pos);
}

void File::read(char* buff, std::streamsize count) {
	checkOpen();
	if (getLength() < getPosition() + count) {
		throw FileException(ErrorMessages::ReadOutOfBounds);
	}
	mFile.read(buff, count);
}

void File::write(const char* data, std::streamsize count) {
	checkOpen();
	mFile.write(data, count);
}

File::PositionType File::getPosition() {
	checkOpen();
	return mFile.tellp();
}

File::PositionType File::getLength() {
	checkOpen();
	auto curPos = mFile.tellg();
	mFile.seekg(0, std::ios::end);
	auto endPos = mFile.tellg();
	mFile.seekg(curPos, std::ios::beg);
	return endPos;
}

void File::checkOpen() const {
	if (!mFile.is_open()) {
		throw FileException(ErrorMessages::FileNotOpen);
	}
}
#include "File.h"
#include "Exception.h"

File::File(const std::string& filename, Mode mode)
{
	open(filename, mode);
}

void File::open(const std::string& filename, Mode mode) {
	if (mFile.is_open()) {
		close();
	}
	if (mode == Mode::Open) {
		mFile.open(filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
	}
	else if(mode == Mode::Trunc) {
		mFile.open(filename, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	}
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
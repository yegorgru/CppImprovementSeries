#include "File.h"

File::File(const std::string& filename)
{
	open(filename);
}

void File::open(const std::string& filename) {
	if (filename.length() == 0) {
		throw std::runtime_error("Empty filename");
	}
	mFilename = filename;
	mFile.open(mFilename, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
	if (!mFile.is_open()) {
		mFile.open(mFilename, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	}
}

void File::close() {
	mFile.close();
	mFilename = "";
}

void File::seek(PositionType pos) {
	checkOpen();
	mFile.seekp(pos);
}

void File::read(char* buff, std::streamsize count) {
	checkOpen();
	if (getLength() < getPosition() + count) {
		throw std::runtime_error("Trying to read data out of file bounds");
	}
	mFile.read(buff, count);
}

void File::write(const char* data, std::streamsize count) {
	checkOpen();
	mFile.write(data, count);
	mFile.flush();
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

void File::checkOpen() {
	if (!mFile.is_open()) {
		throw std::runtime_error("File is not open");
	}
}

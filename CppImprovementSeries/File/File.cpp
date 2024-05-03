#include "File.h"

File::File(const std::string& filename)
{
	open(filename);
}

void File::open(const std::string& filename) {
	mFile.open(filename, std::ios_base::in | std::ios_base::out | std::ios_base::app);
}

void File::close() {
	mFile.close();
}

void File::seek(PositionType pos) {
	checkOpen();
	mFile.seekp(pos);
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
#include "TypeFile.h"

#include <stdexcept>

TypeFile::TypeFile(const std::string& filename) 
{
	open(filename);
}

void TypeFile::open(const std::string& filename) {
	if (filename.ends_with(".metadata")) {
		throw std::runtime_error("filename can't end with .metadata");
	}
	File::open(filename);
	mMetadataFile.open(filename + ".metadata");
	reloadMetadata();
}

void TypeFile::close() {
	File::close();
	mMetadataFile.close();
}

File::PositionType TypeFile::getFieldShift(size_t pos) {
	checkOpen();
	if (pos >= mFieldShifts.size()) {
		throw std::runtime_error("Incorrect field idx or file is empty");
	}
	return mFieldShifts[pos];
}

void TypeFile::writeMetadata(const std::string& metadata) {
	checkOpen();
	mMetadataFile.write(metadata);
}

void TypeFile::reloadMetadata() {
	if (mMetadataFile.getLength() > 0) {
		mMetadataFile.seek(0);
		int pos;
		while (!mMetadataFile.eof()) {
			mMetadataFile.read(pos);
			mFieldShifts.push_back(pos);
		}
	}
}
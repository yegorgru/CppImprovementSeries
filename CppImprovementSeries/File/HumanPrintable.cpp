#include "HumanPrintable.h"

HumanPrintable::HumanPrintable()
{
	setIndexes();
}

HumanPrintable::HumanPrintable(const std::string name, int age)
	: mName(name)
	, mAge(age)
{
	setIndexes();
}

void HumanPrintable::write(TypeFile& file) {
	file.seek(0);
	auto namePos = file.getPosition();
	file.write(mName);
	file.write(" ");
	auto agePos = file.getPosition();
	file.write(mAge);
	file.writeMetadata(std::to_string(namePos) + " " + std::to_string(agePos));
	file.reloadMetadata();
}

void HumanPrintable::read(TypeFile& file) {
	readName(file);
	readAge(file);
}

void HumanPrintable::readName(TypeFile& file) {
	auto pos = file.getFieldShift(getFieldIdx("name"));
	file.seek(pos);
	file.read(mName);
}

void HumanPrintable::readAge(TypeFile& file) {
	auto pos = file.getFieldShift(getFieldIdx("age"));
	file.seek(pos);
	file.read(mAge);
}

void HumanPrintable::setIndexes() {
	mIndexes["name"] = 0;
	mIndexes["age"] = 1;
}
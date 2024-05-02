#pragma once

#include "AbstractPrintable.h"

#include <string>

class HumanPrintable : public AbstractPrintable
{
public:
	HumanPrintable();
	HumanPrintable(const std::string name, int age);
	HumanPrintable(const HumanPrintable& other) = default;
	HumanPrintable& operator=(const HumanPrintable& other) = default;
	HumanPrintable(HumanPrintable&& other) = default;
	HumanPrintable& operator=(HumanPrintable&& other) = default;
	~HumanPrintable() = default;
public:
	const std::string& getName() const {
		return mName;
	}
	int getAge() const {
		return mAge;
	}
	void setName(const std::string& name) {
		mName = name;
	}
	void setAge(int age) {
		mAge = age;
	}
public:
	void write(TypeFile& file) override;
	void read(TypeFile& file) override;
public:
	void readName(TypeFile& file);
	void readAge(TypeFile& file);
private:
	void setIndexes();
private:
	std::string mName;
	int mAge = 0;
};


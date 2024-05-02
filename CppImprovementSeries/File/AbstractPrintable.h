#pragma once

#include "TypeFile.h"

#include <string>
#include <iostream>
#include <sstream>
#include <map>

class AbstractPrintable
{
public:
	AbstractPrintable() = default;
	AbstractPrintable(const AbstractPrintable& other) = default;
	AbstractPrintable& operator=(const AbstractPrintable& other) = default;
	AbstractPrintable(AbstractPrintable&& other) = default;
	AbstractPrintable& operator=(AbstractPrintable&& other) = default;
	virtual ~AbstractPrintable() = default;
public:
	virtual void write(TypeFile& file) = 0;
	virtual void read(TypeFile& file) = 0;
	int getFieldIdx(const std::string& field);
protected:
	using FieldIndexes = std::map<std::string, int>;
protected:
	FieldIndexes mIndexes;
};


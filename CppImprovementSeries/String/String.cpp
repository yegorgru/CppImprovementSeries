#include "String.h"

#include <cstring>

String::String(const char* data)
	: mData(nullptr)
	, mSize(0)
{
	if (!data) {
		return;
	}
	mSize = std::strlen(data) + 1;
	mData = std::make_unique<char[]>(mSize);
	std::memcpy(mData.get(), data, mSize);
}

String::String(const String& copy)
	: mData(nullptr)
	, mSize(0)
{
	copy_internal(copy);
}

String& String::operator=(const String& copy) {
	return copy_internal(copy);
}

String& String::copy_internal(const String& copy) {
	if (this == &copy) {
		return *this;
	}

	mSize = copy.mSize;
	mData.reset();
	if (!mSize) {
		return *this;
	}

	mData = std::make_unique<char[]>(mSize);
	std::memcpy(mData.get(), copy.mData.get(), mSize);

	return *this;
}
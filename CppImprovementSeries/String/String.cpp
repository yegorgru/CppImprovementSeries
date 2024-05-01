#include "String.h"

#include <cstring>
#include <iostream>

String::String(const char* data)
	: mSize(0)
	, mCapacity(0)
{
	if (!data) {
		return;
	}
	mSize = std::strlen(data) + 1;
	mCapacity = mSize;
	mData = std::make_unique<char[]>(mSize);
	std::memcpy(mData.get(), data, mSize);
}

String::String(const String& copy)
	: mSize(0)
	, mCapacity(0)
{
	copyInternal(copy);
}

String& String::operator=(const String& copy) {
	return copyInternal(copy);
}

void String::reserve(size_t newCapacity) {
	reserve(newCapacity, true);
}

std::string String::toString() const {
	return std::string(mData.get());
}

void String::reserve(size_t newCapacity, bool copyData) {
	if (newCapacity > mCapacity) {
		newCapacity = mCapacity * 2 >= newCapacity ? mCapacity * 2 : newCapacity;
		reallocateData(newCapacity, copyData);
		mCapacity = newCapacity;
	}
}

String& String::copyInternal(const String& copy) {
	if (this == &copy) {
		return *this;
	}

	reserve(copy.mSize, false);
	mSize = copy.mSize;
	if (!mSize) {
		mData.reset();
		return *this;
	}

	std::memcpy(mData.get(), copy.mData.get(), mSize);

	return *this;
}

void String::reallocateData(size_t capacity, bool copyData)
{
	Data newData = std::make_unique<char[]>(capacity);
	if (copyData) {
		std::memcpy(newData.get(), mData.get(), mSize);
	}
	mData = std::move(newData);
}

bool String::operator==(const String& other) const {
	return std::strcmp(mData.get(), other.mData.get()) == 0;
}

bool String::operator<(const String& other) const {
	return std::strcmp(mData.get(), other.mData.get()) < 0;
}

bool String::operator>(const String& other) const {
	return std::strcmp(mData.get(), other.mData.get()) > 0;
}

bool String::operator<=(const String& other) const {
	auto res = std::strcmp(mData.get(), other.mData.get());
	return res == 0 || res < 0;
}

bool String::operator>=(const String& other) const {
	auto res = std::strcmp(mData.get(), other.mData.get());
	return res == 0 || res > 0;
}

String String::operator+(const String& other) {
	String result = *this;
	result += other;
	return result;
}

String& String::operator+=(const String& other) {
	reserve(mSize + other.mSize);
	std::memcpy(mData.get() + getSize(), other.mData.get(), other.mSize);
	return *this;
}

String::operator const char*() const {
	return mData.get();
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	os << str.mData.get();
	return os;
}
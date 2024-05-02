#include "String.h"

#include <cstring>

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

String::String(const std::string& data)
	: String(data.c_str())
{

}

String::String(const String& other)
	: mSize(0)
	, mCapacity(0)
{
	copyInternal(other);
}

String& String::operator=(const String& other) {
	return copyInternal(other);
}

void String::reserve(size_t newCapacity) {
	reserve(newCapacity, true);
}

std::string String::toString() const {
	auto ptr = mData.get();
	return ptr == nullptr ? "" : std::string(ptr);
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
		auto ptr = mData.get();
		if (ptr) {
			std::memcpy(newData.get(), ptr, mSize);
		}
	}
	mData = std::move(newData);
}

bool String::operator==(const String& other) const {
	const char* lhs = mData.get() ? mData.get() : "";
	const char* rhs = other.mData.get() ? other.mData.get() : "";
	return getSize() == other.getSize() && std::strcmp(lhs, rhs) == 0;
}

bool String::operator<(const String& other) const {
	const char* lhs = mData.get() ? mData.get() : "";
	const char* rhs = other.mData.get() ? other.mData.get() : "";
	return std::strcmp(lhs, rhs) < 0;
}

bool String::operator>(const String& other) const {
	const char* lhs = mData.get() ? mData.get() : "";
	const char* rhs = other.mData.get() ? other.mData.get() : "";
	return std::strcmp(lhs, rhs) > 0;
}

bool String::operator<=(const String& other) const {
	const char* lhs = mData.get() ? mData.get() : "";
	const char* rhs = other.mData.get() ? other.mData.get() : "";
	auto res = std::strcmp(lhs, rhs);
	return res == 0 || res < 0;
}

bool String::operator>=(const String& other) const {
	const char* lhs = mData.get() ? mData.get() : "";
	const char* rhs = other.mData.get() ? other.mData.get() : "";
	auto res = std::strcmp(lhs, rhs);
	return res == 0 || res > 0;
}

String String::operator+(const String& other) {
	String result = *this;
	result += other;
	return result;
}

String& String::operator+=(const String& other) {
	if (!mSize) {
		*this = other;
	}
	else if (other.mSize) {
		reserve(mSize + other.mSize);
		std::memcpy(mData.get() + getSize(), other.mData.get(), other.mSize);
		mSize = mSize + other.mSize - 1;
	}
	return *this;
}

String::operator const char* () const {
	return mData.get() ? mData.get() : nullptr;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	auto ptr = str.mData.get();
	if (ptr) {
		os << ptr;
	}
	return os;
}
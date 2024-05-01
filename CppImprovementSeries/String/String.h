#pragma once

#include <memory>

class String {
public:
	String(const char* data = nullptr);
	String(const String& copy);
	String& operator=(const String& copy);
	String(String&& copy) = default;
	String& operator=(String&& copy) = default;
	~String() = default;
public:
	size_t getSize() const { 
		return mSize == 0 ? 0 : mSize - 1;
	}
private:
	String& copy_internal(const String& copy);
private:
	using Data = std::unique_ptr<char[]>;
public:
	size_t mSize;
	Data mData;
};
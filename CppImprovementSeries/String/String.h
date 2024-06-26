#pragma once

#include <memory>
#include <string>
#include <iostream>

class String {
public:
	String(const char* data = nullptr);
	String(const std::string& data);
	String(const String& other);
	String& operator=(const String& other);
	String(String&& other);
	String& operator=(String&& other);
	~String() = default;
public:
	void reserve(size_t newCapacity);
	std::string toString() const;
public:
	size_t getSize() const {
		return mSize == 0 ? 0 : mSize - 1;
	}
	size_t getCapacity() const {
		return mCapacity;
	}
public:
	bool operator==(const String& other) const;
	bool operator<(const String& other) const;
	bool operator>(const String& other) const;
	bool operator<=(const String& other) const;
	bool operator>=(const String& other) const;
	String operator+(const String& other);
	String& operator+=(const String& other);
	operator const char*() const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
private:
	void reserve(size_t newCapacity, bool copyData);
	String& copyInternal(const String& other);
	String& moveInternal(String&& other);
	void reallocateData(size_t capacity, bool copyData);
private:
	using Data = std::unique_ptr<char[]>;
private:
	size_t mSize;
	size_t mCapacity;
	Data mData;
};

std::ostream& operator<<(std::ostream& os, const String& str);
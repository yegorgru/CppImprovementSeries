#pragma once

#include <memory>
#include <string>

class String {
public:
	String(const char* data = nullptr);
	String(const String& copy);
	String& operator=(const String& copy);
	String(String&& copy) = default;
	String& operator=(String&& copy) = default;
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
	operator const char* () const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
private:
	void reserve(size_t newCapacity, bool copyData);
	String& copyInternal(const String& copy);
	void reallocateData(size_t capacity, bool copyData);
private:
	using Data = std::unique_ptr<char[]>;
private:
	size_t mSize;
	size_t mCapacity;
	Data mData;
};

std::ostream& operator<<(std::ostream& os, const String& str);
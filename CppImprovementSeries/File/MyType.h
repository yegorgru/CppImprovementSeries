#pragma once

#include <array>
#include <iostream>

class MyType
{
public:
	using Coords = std::array<double, 3>;
public:
	MyType() = default;
	MyType(double x, double y, double z);
	MyType(const MyType& other) = default;
	MyType& operator=(const MyType& other) = default;
	MyType(MyType&& other) = default;
	MyType& operator=(MyType&& other) = default;
	~MyType() = default;
public:
	Coords& getCoords() {
		return mCoords;
	}
	const Coords& getCoords() const {
		return mCoords;
	}
private:
	Coords mCoords;
};

std::ostream& operator<<(std::ostream& os, const MyType& type);
std::istream& operator>>(std::istream& is, MyType& type);

#include "MyType.h"

MyType::MyType(double x, double y, double z)
	: mCoords({x, y, z})
{

}

std::ostream& operator<<(std::ostream& os, const MyType& type) {
	const auto& coords = type.getCoords();
	os << coords[0] << " " << coords[1] << " " << coords[2];
	return os;
}

std::istream& operator>>(std::istream& is, MyType& type) {
	auto& coords = type.getCoords();
	is >> coords[0] >> coords[1] >> coords[2];
	return is;
}
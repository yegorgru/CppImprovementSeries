#include "View.h"

#include "Exception.h"

std::string View::getStringLine() const {
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::string str;
	std::getline(std::cin, str);
	if (std::cin.rdbuf()->in_avail() > 0) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return str;
}
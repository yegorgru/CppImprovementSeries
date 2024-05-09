#include "View.h"

#include <stdexcept>

ActionCode View::runMenuItem() {
	if (!mMenuRoot) {
		throw std::runtime_error("Root menu item was not set");
	}
	if (!mMenuItem) {
		mMenuItem = mMenuRoot;
	}
	auto actionResult = mMenuItem->makeAction();
	mMenuItem = actionResult.first;
	return mMenuItem ? actionResult.second : ActionCode::Exit;
}

std::string View::getStringLine() {
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
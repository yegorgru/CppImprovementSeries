#pragma once

#include "AbstractLevel.h"

#include <string>
#include <iostream>

class View
{
public:
	View() = default;
	View(const View& other) = delete;
	View& operator=(const View& other) = delete;
	View(View&& other) = default;
	View& operator=(View&& other) = default;
	~View() = default;
public:
	Menu::AbstractLevel::ActionCode runMenuItem();
	std::string getStringLine();
	template <typename... Args>
	void showMessage(const Args&... args);
	template <typename... Args>
	void showErrorMessage(const Args&... args);
public:
	void setMenuRoot(Menu::AbstractLevelPtr menuRoot) {
		mMenuRoot = menuRoot;
	}
private:
	Menu::AbstractLevelPtr mMenuRoot;
	Menu::AbstractLevelPtr mMenuItem;
};

template <typename... Args>
void View::showMessage(const Args&... args) {
	(std::cout << ... << args) << std::endl;
}

template <typename... Args>
void View::showErrorMessage(const Args&... args) {
	(std::cerr << ... << args) << std::endl;
}
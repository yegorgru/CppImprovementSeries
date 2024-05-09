#pragma once

#include "AbstractLevel.h"
#include "ActionCode.h"

#include <string>
#include <iostream>

class View
{
public:
	using MenuItemPtr = Menu::AbstractLevel<ActionCode>::AbstractLevelPtr;
public:
	View() = default;
	View(const View& other) = delete;
	View& operator=(const View& other) = delete;
	View(View&& other) = default;
	View& operator=(View&& other) = default;
	~View() = default;
public:
	ActionCode runMenuItem();
	std::string getStringLine();
	template <typename... Args>
	void showMessage(const Args&... args);
	template <typename... Args>
	void showErrorMessage(const Args&... args);
public:
	void setMenuRoot(MenuItemPtr menuRoot) {
		mMenuRoot = menuRoot;
	}
private:
	MenuItemPtr mMenuRoot;
	MenuItemPtr mMenuItem;
};

template <typename... Args>
void View::showMessage(const Args&... args) {
	(std::cout << ... << args) << std::endl;
}

template <typename... Args>
void View::showErrorMessage(const Args&... args) {
	(std::cerr << ... << args) << std::endl;
}
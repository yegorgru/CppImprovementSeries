#pragma once

#include "ActionCode.h"

#include <string>
#include <iostream>
#include <vector>

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
	ActionCode runMenu();
	std::string getStringLine();
	template <typename... Args>
	void showMessage(const Args&... args);
	template <typename... Args>
	void showErrorMessage(const Args&... args);
public:
	class Messages {
	public:
		using MenuMessages = std::vector<std::string>;
	public:
		inline static const std::string MenuTitle = "\tMENU";
		inline static const std::string EnterChoice = "Enter your choice: ";
		inline static const MenuMessages MenuItems = {
			"1  - Create/truncate plain file",
			"2  - Open and append plain file",
			"3  - Close plain file",
			"4  - Seek plain file",
			"5  - Get position plain file",
			"6  - Get length plain file",
			"7  - Read int plain file",
			"8  - Read string plain file",
			"9  - Read double plain file",
			"10 - Write int plain file",
			"11 - Write string plain file",
			"12 - Write double plain file",
			"13 - Create/truncate data file",
			"14 - Open and append data file",
			"15 - Close data file",
			"16 - Read data",
			"17 - Set data",
			"18 - Append data",
			"19 - Get data count",
			"0  - Exit"
		};
	};

	class ErrorMessages {
	public:
		inline static const std::string IncorrectUserInput = "Incorrect user input";
	};
};

template <typename... Args>
void View::showMessage(const Args&... args) {
	(std::cout << ... << args) << std::endl;
}

template <typename... Args>
void View::showErrorMessage(const Args&... args) {
	(std::cerr << ... << args) << std::endl;
}
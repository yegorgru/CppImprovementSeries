#pragma once

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
	std::string getStringLine() const;
	template <typename T>
	bool safeInput(T& v) const;
	template <typename... Args>
	void showMessage(const Args&... args) const;
	template <typename... Args>
	void showErrorMessage(const Args&... args) const;
};

template <class T>
bool View::safeInput(T& v) const {
	bool result = (std::cin >> v) && (std::cin.get() == '\n');
	if (std::cin.fail() || !result) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return result;
}

template <typename... Args>
void View::showMessage(const Args&... args) const {
	(std::cout << ... << args) << std::endl;
}

template <typename... Args>
void View::showErrorMessage(const Args&... args) const {
	(std::cerr << ... << args) << std::endl;
}
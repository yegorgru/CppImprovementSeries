#pragma once

#include "View.h"

#include <functional>
#include <map>

class Application
{
public:
	class Messages {
	public:
		inline static const std::string MenuTitle = "\tMENU";
		inline static const std::string EnterChoice = "Enter your choice: ";
		inline static const std::string Exit = "Exiting";
	};

	class ErrorMessages {
	public:
		inline static const std::string IncorrectUserInput = "Incorrect user input";
		inline static const std::string UnsupportedMenuKey = "Unsupported menu key";
		inline static const std::string MenuKeyAlreadyUsed = "This menu key is already used";
		inline static const std::string ErrorHappened = "Error happened: ";
	};
public:
	Application(const View& view);
	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = default;
	Application& operator=(Application&& other) = default;
	~Application() = default;
public:
	void run();
	void registerMenuItem(int code, const std::string& title, const std::function<void()>& func);
	void setExitFlag() {
		mExitFlag = true;
	}
private:
	int runMenu();
private:
	struct MenuItem {
		std::string mTitle;
		std::function<void()> mCommand;
	};
private:
	using MenuDictionary = std::map<int, MenuItem>;
private:
	bool mExitFlag;
	const View& mView;
	MenuDictionary mMenuDictionary;
};
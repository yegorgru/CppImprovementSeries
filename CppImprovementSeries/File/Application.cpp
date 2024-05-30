#include "Application.h"
#include "Exception.h"

#include <sstream>

Application::Application(const View& view)
	: mExitFlag(false)
	, mView(view)
{

}

void Application::run() {
	while (!mExitFlag) {
		try
		{
			auto menuKey = runMenu();
			auto menuItem = mMenuDictionary.find(menuKey);
			if (menuItem != mMenuDictionary.end()) {
				menuItem->second.mCommand();
			}
			else {
				mView.showErrorMessage(ErrorMessages::UnsupportedMenuKey);
			}
		}
		catch (const Exception& ex)
		{
			mView.showErrorMessage(ErrorMessages::ErrorHappened, ex.what());
		}
	}
	mView.showMessage(Messages::Exit);
}

void Application::registerMenuItem(int code, const std::string& title, const std::function<void()>& func) {
	auto found = mMenuDictionary.find(code);
	if (found != mMenuDictionary.end()) {
		mView.showErrorMessage(ErrorMessages::MenuKeyAlreadyUsed);
		return;
	}
	mMenuDictionary[code] = { title, func };
}

int Application::runMenu() {
	int userChoice = -1;
	while (userChoice == -1) {
		mView.showMessage(Messages::MenuTitle);
		for (const auto& menuItem : mMenuDictionary) {
			mView.showMessage(menuItem.first, " - ", menuItem.second.mTitle);
		}
		mView.showMessage(Messages::EnterChoice);
		if (!mView.safeInput(userChoice)) {
			userChoice = -1;
			throw InputException(ErrorMessages::IncorrectUserInput);
		}
		else {
			return userChoice;
		}
	}
}
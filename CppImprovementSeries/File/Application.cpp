#include "Application.h"
#include "Exception.h"

#include <sstream>

void Application::run() {
	while (!mExitFlag) {
		try
		{
			auto menuKey = runMenu();
			auto menuItem = mMenuDictionary.find(menuKey);
			if (menuItem != mMenuDictionary.end()) {
				menuItem->second.mCommand(mView);
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

void Application::registerMenuItem(int code, const std::string& title, const std::function<void(const View&)>& func) {
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
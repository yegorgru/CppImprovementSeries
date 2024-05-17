#include "View.h"

#include "Exception.h"

namespace {
	template <class T>
	bool safeInput(T& v) {
		bool result = (std::cin >> v) && (std::cin.get() == '\n');
		if (std::cin.fail() || !result) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		return result;
	}
}

ActionCode View::runMenu() {
	int userChoice = -1;
	while (userChoice == -1) {
		showMessage(Messages::MenuTitle);
		for (const auto& menuItem : Messages::MenuItems) {
			showMessage(menuItem);
		}
		if (showMessage(Messages::EnterChoice), !safeInput(userChoice)) {
			userChoice = -1;
			throw InputException(ErrorMessages::IncorrectUserInput);
		}
		else {
			switch (userChoice) {
			case 1: return ActionCode::CreateFile;
			case 2: return ActionCode::OpenFile;
			case 3: return ActionCode::CloseFile;
			case 4: return ActionCode::SeekFile;
			case 5: return ActionCode::GetPositionFile;
			case 6: return ActionCode::GetLengthFile;
			case 7: return ActionCode::ReadIntFile;
			case 8: return ActionCode::ReadStringFile;
			case 9: return ActionCode::ReadDoubleFile;
			case 10: return ActionCode::WriteIntFile;
			case 11: return ActionCode::WriteStringFile;
			case 12: return ActionCode::WriteDoubleFile;
			case 13: return ActionCode::CreateDataFile;
			case 14: return ActionCode::OpenDataFile;
			case 15: return ActionCode::CloseDataFile;
			case 16: return ActionCode::ReadDataFile;
			case 17: return ActionCode::SetDataFile;
			case 18: return ActionCode::AppendDataFile;
			case 19: return ActionCode::GetCountDataFile;
			case 0: return ActionCode::Exit;
			default: return ActionCode::UnsupportedKey;
			}
		}
	}
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
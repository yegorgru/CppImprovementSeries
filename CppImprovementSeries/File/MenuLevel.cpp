#include "MenuLevel.h"
#include "utilities.h"

#include <iostream>
#include <stdexcept>
#include <limits>

namespace Menu {

	MenuLevel::MenuLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent)
		: AbstractLevel(symbol, description, parent)
	{

	}

	AbstractLevel::ActionResult MenuLevel::makeAction() const {
		while (true) {
			printNextOptions();
			if (std::cin.rdbuf()->in_avail() > 0) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			char ch = std::getchar();
			auto found = mChildren.find(ch);
			if (found != mChildren.end()) {
				return { found->second, 0 };
			}
			else if (ch == getBackSymbol() && !is_uninitialized(mParent)) {
				return { mParent.lock(), 0 };
			}
			else if (ch == getExitSymbol()) {
				return { nullptr, 0 };
			}
		}
	}

	void MenuLevel::addChild(AbstractLevelPtr child) {
		mChildren[child->getSymbol()] = child;
	}

	void MenuLevel::printNextOptions() const {
		for (auto child : mChildren) {
			child.second->printLevel();
			std::cout << " ";
		}
		if (!is_uninitialized(mParent)) {
			std::cout << getBackSymbol() << " - back" << " ";
		}
		std::cout << getExitSymbol() << " - exit";
		std::cout << std::endl;
	}

}
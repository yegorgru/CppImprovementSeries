#pragma once

#include "AbstractLevel.h"
#include "utilities.h"

#include <map>
#include <string>
#include <functional>

namespace Menu {

	template<typename TActionCode>
	class MenuLevel : public AbstractLevel<TActionCode>
	{
	public:
		using MenuSymbol = AbstractLevel<TActionCode>::MenuSymbol;
		using Description = AbstractLevel<TActionCode>::Description;
		using AbstractLevelPtr = AbstractLevel<TActionCode>::AbstractLevelPtr;
		using ActionResult = AbstractLevel<TActionCode>::ActionResult;
	public:
		MenuLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& code);
		MenuLevel(const MenuLevel& other) = delete;
		MenuLevel& operator=(const MenuLevel& other) = delete;
		MenuLevel(MenuLevel&& other) = default;
		MenuLevel& operator=(MenuLevel&& other) = default;
		~MenuLevel() = default;
	public:
		ActionResult makeAction() const override;
		void addChild(AbstractLevelPtr child);
	private:
		void printNextOptions() const;
	private:
		using ChildrenStorage = std::map<MenuSymbol, AbstractLevelPtr>;
	private:
		ChildrenStorage mChildren;
	};

	template<typename TActionCode>
	MenuLevel<TActionCode>::MenuLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const TActionCode& code)
		: AbstractLevel<TActionCode>(symbol, description, parent, code)
	{

	}

	template<typename TActionCode>
	MenuLevel<TActionCode>::ActionResult MenuLevel<TActionCode>::makeAction() const {
		while (true) {
			printNextOptions();
			if (std::cin.rdbuf()->in_avail() > 0) {
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			char ch = std::getchar();
			auto found = mChildren.find(ch);
			if (found != mChildren.end()) {
				return { found->second, AbstractLevel<TActionCode>::mCode };
			}
			else if (ch == AbstractLevel<TActionCode>::getBackSymbol() && !is_uninitialized(AbstractLevel<TActionCode>::mParent)) {
				return { AbstractLevel<TActionCode>::mParent.lock(), AbstractLevel<TActionCode>::mCode };
			}
			else if (ch == AbstractLevel<TActionCode>::getExitSymbol()) {
				return { nullptr, AbstractLevel<TActionCode>::mCode };
			}
		}
	}

	template<typename TActionCode>
	void MenuLevel<TActionCode>::addChild(AbstractLevelPtr child) {
		mChildren[child->getSymbol()] = child;
	}
	
	template<typename TActionCode>
	void MenuLevel<TActionCode>::printNextOptions() const {
		for (auto child : mChildren) {
			child.second->printLevel();
			std::cout << " ";
		}
		if (!is_uninitialized(AbstractLevel<TActionCode>::mParent)) {
			std::cout << AbstractLevel<TActionCode>::getBackSymbol() << " - back" << " ";
		}
		std::cout << AbstractLevel<TActionCode>::getExitSymbol() << " - exit";
		std::cout << std::endl;
	}

}
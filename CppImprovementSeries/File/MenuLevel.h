#pragma once

#include "AbstractLevel.h"

#include <map>
#include <string>
#include <functional>

namespace Menu {

	class MenuLevel : public AbstractLevel
	{
	public:
		MenuLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent);
		MenuLevel(const MenuLevel& other) = delete;
		MenuLevel& operator=(const MenuLevel& other) = delete;
		MenuLevel(MenuLevel&& other) = default;
		MenuLevel& operator=(MenuLevel&& other) = default;
		~MenuLevel() = default;
	public:
		AbstractLevelPtr makeAction() const override;
		void addChild(AbstractLevelPtr child);
	private:
		void printNextOptions() const;
	private:
		using ChildrenStorage = std::map<MenuSymbol, AbstractLevelPtr>;
	private:
		ChildrenStorage mChildren;
	};

}
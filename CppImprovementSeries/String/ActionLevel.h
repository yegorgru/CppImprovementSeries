#pragma once

#include "AbstractLevel.h"

#include <functional>

namespace Menu {

class ActionLevel : public AbstractLevel
{
public:
	using Function = std::function<void()>;
public:
	ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const Function& function);
	ActionLevel(const ActionLevel& other) = delete;
	ActionLevel& operator=(const ActionLevel& other) = delete;
	ActionLevel(ActionLevel&& other) = default;
	ActionLevel& operator=(ActionLevel&& other) = default;
	~ActionLevel() = default;
public:
	AbstractLevelPtr makeAction() override;
private:
	Function mFunction;
};

}
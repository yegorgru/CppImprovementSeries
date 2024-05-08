#pragma once

#include "AbstractLevel.h"

#include <functional>

namespace Menu {

	class ActionLevel : public AbstractLevel
	{
	public:
		ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const ActionCode& code);
		ActionLevel(const ActionLevel& other) = delete;
		ActionLevel& operator=(const ActionLevel& other) = delete;
		ActionLevel(ActionLevel&& other) = default;
		ActionLevel& operator=(ActionLevel&& other) = default;
		~ActionLevel() = default;
	public:
		ActionResult makeAction() const override;
	private:
		ActionCode mCode;
	};

}
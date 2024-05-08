#include "ActionLevel.h"

#include <stdexcept>

namespace Menu {

	ActionLevel::ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const ActionCode& code)
		: AbstractLevel(symbol, description, parent)
		, mCode(code)
	{

	}

	AbstractLevel::ActionResult ActionLevel::makeAction() const {
		return { mParent.lock(), mCode };
	}

}
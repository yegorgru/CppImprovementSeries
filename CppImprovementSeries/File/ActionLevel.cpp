#include "ActionLevel.h"

#include <stdexcept>

namespace Menu {

	ActionLevel::ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const Function& function)
		: AbstractLevel(symbol, description, parent)
		, mFunction(function)
	{

	}

	AbstractLevelPtr ActionLevel::makeAction() const {
		mFunction();
		return mParent.lock();
	}

}
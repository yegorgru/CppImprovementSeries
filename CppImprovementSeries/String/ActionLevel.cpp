#include "ActionLevel.h"

#include <stdexcept>

namespace Menu {

ActionLevel::ActionLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent, const Function& function)
	: AbstractLevel(Type::ActionItem, symbol, description, parent)
	, mFunction(function)
{

}

AbstractLevelPtr ActionLevel::makeAction() {
	mFunction();
	return mParent.lock();
}

}
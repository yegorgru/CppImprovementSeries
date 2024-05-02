#include "AbstractLevel.h"

#include <stdexcept>
#include <iostream>

namespace Menu {

AbstractLevel::AbstractLevel(MenuSymbol symbol, const Description& description, AbstractLevelPtr parent)
	: mSymbol(symbol)
	, mDescription(description)
	, mParent(parent)
{
	if (getBackSymbol() == mSymbol || getExitSymbol() == mSymbol) {
		throw std::runtime_error("Incorrect menu symbol provided");
	}
}

void AbstractLevel::printLevel() const {
	std::cout << mSymbol << " - " << mDescription;
}

}
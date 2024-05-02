#include "AbstractLevel.h"

#include <stdexcept>
#include <iostream>

namespace Menu {

AbstractLevel::AbstractLevel(Type type, MenuSymbol symbol, const Description& description, AbstractLevelPtr parent)
	: mType(type)
	, mSymbol(symbol)
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
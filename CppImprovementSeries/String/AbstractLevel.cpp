#include "AbstractLevel.h"

#include <stdexcept>
#include <iostream>

namespace Menu {

AbstractLevel::AbstractLevel(Type type, MenuSymbol symbol, const Description& description, AbstractLevelPtr parent)
	: mType(type)
	, mDescription(description)
	, mSymbol(symbol)
	, mParent(parent)
{
	if (getBackSymbol() == mSymbol || getExitSymbol() == mSymbol) {
		throw std::runtime_error("Incorrect menu symbol provided");
	}
}

void AbstractLevel::printLevel() {
	std::cout << mSymbol << " - " << mDescription;
}

}
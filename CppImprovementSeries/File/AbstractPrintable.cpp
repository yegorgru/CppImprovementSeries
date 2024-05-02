#include "AbstractPrintable.h"

#include <stdexcept>

int AbstractPrintable::getFieldIdx(const std::string& field) {
	auto found = mIndexes.find(field);
	if (found == mIndexes.end()) {
		throw std::runtime_error("Incorrect field provided");
	}
	else {
		return found->second;
	}
}
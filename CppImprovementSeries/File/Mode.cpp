#include "Mode.h"

#include <type_traits>

Mode operator|(Mode lhs, Mode rhs) {
	return static_cast<Mode>(
		static_cast<std::underlying_type<Mode>::type>(lhs) |
		static_cast<std::underlying_type<Mode>::type>(rhs)
	);
}

bool hasMode(Mode modes, Mode mode) {
	return static_cast<Mode>(
		static_cast<std::underlying_type<Mode>::type>(modes) &
		static_cast<std::underlying_type<Mode>::type>(mode)
	) == mode;
}
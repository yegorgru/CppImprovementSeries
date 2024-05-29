#pragma once

enum class Mode : unsigned int {
	Open = 1,
	Create = 1 << 1,
	Trunc = 1 << 2,
	Ate = 1 << 3,
	Binary = 1 << 4,
};

Mode operator|(Mode lhs, Mode rhs);

bool hasMode(Mode modes, Mode mode);
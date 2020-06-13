#pragma once

#include "FVector.h"

namespace Shader {
#include "VS.shh"
#include "PS.shh"
};

struct PCT_VERTEX {
	FVector3 p;
	FVector4 c;
	FVector2 t;

	static inline constexpr unsigned int POSITION = sizeof(decltype(p));
	static inline constexpr unsigned int COLOR = sizeof(decltype(c));
	static inline constexpr unsigned int UV = sizeof(decltype(t));
};

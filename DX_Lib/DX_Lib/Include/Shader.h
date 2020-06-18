#pragma once

#include "FVector.h"

namespace Shader {
	#include "VS.shh"
	#include "PS.shh"
};

struct VS_CB {
	float r, g, b, a;
	float x, y, z, Time;
	float sx, sy, sz, angle;
	float rsx, rsy, rsz, rsx_padding;
	float scx, scy, scz, scx_padding;
	float uvtop, uvbottom, _1, _2;
};

struct PCT_VERTEX {
	FVector3 p;
	FVector4 c;
	FVector2 t;

	static inline constexpr unsigned int POSITION = sizeof(decltype(p));
	static inline constexpr unsigned int COLOR = sizeof(decltype(c));
	static inline constexpr unsigned int UV = sizeof(decltype(t));
};

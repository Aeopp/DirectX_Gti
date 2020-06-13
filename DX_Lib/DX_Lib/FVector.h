#pragma once

struct FVector2 {
	FVector2() = default;
	FVector2(const int x, const int y) :
		x{ static_cast<float>(x) }, y{ static_cast<float>(y) }{};
	FVector2(const float x, const float y) :
		x{x}, y{y}		{};
	float x{};
	float y{};
};
struct FVector3 {
	FVector3() = default;
	FVector3(const int x, const int y, const int z) :
		x{ static_cast<float>(x) }, y{ static_cast<float>( y) }, z{ static_cast<float>(z)}{};
	FVector3(const float x, const float y,const float z) :
		x{ x }, y{ y }, z{z}	{};
	float x{};
	float  y{};
	float z{};
};
struct FVector4 {
	FVector4() = default;
	FVector4(const float x, const float y, const float z,const float w) :
		x{ x }, y{ y }, z{ z }, w{w}{};
	FVector4(const int x, const int y, const int z,const int w) :
		x{ static_cast<float>(x) }, y{ static_cast<float>(y) }, 
		z{ static_cast<float>(z) }, w{ static_cast<float>(w) } {};
	float x{}; float  y{}; float  z{}; float  w{};
};


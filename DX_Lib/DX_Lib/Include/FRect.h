#pragma once
#include <Windows.h>

struct FRect {
	FRect(long left, long top, long right, long bottom) :
		left{ static_cast<float>(left) },
		top{ static_cast<float>(top) },
		right{ static_cast<float>(right) },
		bottom{ static_cast<float>(bottom) }{};

	FRect(float left, float top, float right, float bottom) :
		left{ left },
		top{ top },
		right{ right },
		bottom{ bottom }{};

	FRect(const RECT& Rhs) :
		FRect(Rhs.left, Rhs.top, Rhs.right, Rhs.bottom) {};

	operator RECT()noexcept
	{
		return RECT{
			static_cast<LONG>(this->left),
			static_cast<LONG>(this->top) ,
			static_cast<LONG>(this->right),
			static_cast<LONG> (this->bottom) };
	};

	FRect() = default;

	float left{ 0 };  float  top{ 0 }; float right{ 0 }; float  bottom{ 0 };
};

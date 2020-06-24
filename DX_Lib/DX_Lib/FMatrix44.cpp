#include "FMatrix44.h"
#include "FVector.h"
void FMatrix44::Scale(const FVector3& V)
{
	_11 = V.x; _22 = V.y; _33 = V.z;
}

void FMatrix44::XRotate(const float Radian)
{
	float fCos = cos(Radian);
	float fSin = sin(Radian);
	_22 = fCos; _23 = fSin;
	_32 = -fSin; _33 = fCos;
}

void FMatrix44::YRotate(const float Radian)
{
	float fCos = cos(Radian);
	float fSin = sin(Radian);
	_11 = fCos; _13 = -fSin;
	_31 = fSin; _33 = fCos;
}

void FMatrix44::ZRotate(const float Radian)
{
	float fCos = cos(Radian);
	float fSin = sin(Radian);
	_11 = fCos; _12 = fSin;
	_21 = -fSin; _22 = fCos;
}

void FMatrix44::Translation(const FVector3& V)
{
	_41 = V.x; _42 = V.y; _43 = V.z;
}

FMatrix44 FMatrix44::Transpose()
{
	FMatrix44 ret;
	ret._11 = _11; ret._12 = _21; ret._13 = _31; ret._14 = _41;
	ret._21 = _12; ret._22 = _22; ret._23 = _32; ret._24 = _42;
	ret._31 = _13; ret._32 = _23; ret._33 = _33; ret._34 = _43;
	ret._41 = _14; ret._42 = _24; ret._43 = _34; ret._44 = _44;
	return ret;
}

FMatrix44 FMatrix44::Inverse()
{
	FMatrix44 ret;
	return ret;
}

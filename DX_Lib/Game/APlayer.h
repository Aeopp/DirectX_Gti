#pragma once
#include "AActor.h"
class APlayer :public AActor
{
	friend class UWorld; 
	using Super = AActor;
public :
	bool Init()noexcept;
private:
	APlayer();
	virtual ~APlayer()noexcept;
};


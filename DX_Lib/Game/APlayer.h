#pragma once
#include "AActor.h"
class APlayer :public AActor
{
	friend class UWorld; 
	using Super = AActor;
public :
	bool Init()noexcept;
	
	bool Release()noexcept override;
	bool Frame(float DeltaTime)override;
	bool Render(float DeltaTime)override;
private:
	APlayer();
	virtual ~APlayer()noexcept;
};


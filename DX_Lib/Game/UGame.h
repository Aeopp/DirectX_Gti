#pragma once
#include "UCore.h"
#include "SingleTon.h"

#include <string>

#pragma comment(lib, "fmod_vc.lib")

class UGame  : public UCore, public SingleTon<UGame>
{
public :
	bool Render(float DeltaTime)override;
	bool Init()override;
	bool Frame(float DeltaTime)override;
	bool Release()override;

	static inline const float DefaultFontSize{ 50.f };
private:
	DECLARE_SINGLETON(UGame)
};


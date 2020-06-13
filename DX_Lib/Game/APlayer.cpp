#include "APlayer.h"

#include "UWorld.h"
#include "UMesh.h"
#include "UDevice.h"
#include "UTimer.h"

#include "DataTable.h"

APlayer::APlayer()
	:AActor()
{
	auto Mesh = UWorld::Instance().CreateObject<UMesh>(this);

	GetMesh()->Create(path::w::DefaultResourcePath + path::w::IMAGE, 
	{ 200.f,200.f,400.f,400.f }, this);
};

bool APlayer::Init()noexcept {
	AActor::Init();

	return true; 
}

APlayer::~APlayer() noexcept
{
}

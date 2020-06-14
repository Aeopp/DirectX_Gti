#include "APlayer.h"

#include "UWorld.h"
#include "UMesh.h"
#include "UDevice.h"
#include "UTimer.h"
#include "UInput.h"

#include "DataTable.h"

APlayer::APlayer()
	:AActor()
{
	auto Mesh = UWorld::Instance().CreateObject<UMesh>(this);

	GetMesh()->Create(path::w::DefaultResourcePath + path::w::IMAGE, 
	{ 200.f,200.f,400.f,400.f }, this,
		UMesh::ELayer::BackGround);

	/*UInput::Instance().EventRegist(
		[SoundPath = path::s::DefaultResourcePath + path::s::WhenTheMorningComess](float) {
		USound::Instance().Play(SoundPath, true);
	}, EKeyState::Press, DIK_F2);*/
};

bool APlayer::Init()noexcept {
	AActor::Init();

	return true; 
}

APlayer::~APlayer() noexcept
{
}

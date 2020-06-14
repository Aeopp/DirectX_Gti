#include "APlayer.h"

#include "UWorld.h"
#include "UMesh.h"
#include "UDevice.h"
#include "UTimer.h"
#include "UInput.h"

#include "FVector.h"

#include "DataTable.h"

APlayer::APlayer()
	:AActor()
{
	auto Mesh = UWorld::Instance().CreateObject<UMesh>(this);

	GetMesh()->Create(path::w::DefaultResourcePath + path::w::IMAGE, 
	{ 0.f,0.f,100.f,100.f}, this,
		UMesh::ELayer::BackGround);

	auto Forward = [this](float dt) {
		auto [x,y,z] =  GetLocation();
		x+= dt * 100.f;
		SetLocation(FVector3{ x,y,z });
	};

	auto Back = [this](float dt) {
		auto [x, y, z] = GetLocation();
		x -= dt * 100.f;
		SetLocation(FVector3{ x,y,z });
	};
	SetVelocity(FVector3{ 10,10,10 });

	UInput::Instance().EventRegist([this](float dt) {
		MoveForward(dt);
		}, EKeyState::Hold, DIK_UP);
	using namespace std::placeholders;

	UInput::Instance().EventRegist(std::bind(&APlayer::MoveBackward,this,_1), EKeyState::Hold, DIK_DOWN);
	UInput::Instance().EventRegist(std::bind(&AActor::MoveBackward, this,_1), EKeyState::Hold, DIK_DOWN);
	UInput::Instance().EventRegist(std::bind(&AActor::MoveLeft, this,_1), EKeyState::Hold, DIK_LEFT);
	UInput::Instance().EventRegist(std::bind(&AActor::MoveRight, this,_1), EKeyState::Hold, DIK_RIGHT);
};

bool APlayer::Init()noexcept {
	AActor::Init();

	return true; 
}

APlayer::~APlayer() noexcept
{
}

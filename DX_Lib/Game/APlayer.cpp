#include "APlayer.h"

#include "UWorld.h"
#include "UMesh.h"
#include "UDevice.h"
#include "UTimer.h"
#include "UInput.h"
#include "FVector.h"

#include "FMath.h"
#include "DataTable.h"

APlayer::APlayer() :AActor() {
	auto Mesh = UWorld::Instance().CreateObject<UMesh>(this);

	GetMesh()->Create(path::w::DefaultResourcePath + path::w::IMAGE,
		{ 0.f,0.f,250.f,224.f }, this, UMesh::ELayer::Character);

	SetLocation({0.f,0.f, 0.f});

	GetMesh()->SetAnim(path::w::DefaultPlayerPath +L"Left\\SWING1.png", 3,0,0.2f, L"SWING1");
	GetMesh()->SetAnim(path::w::DefaultPlayerPath +L"Left\\SWING2.png", 3,0,0.2f, L"SWING2");
	GetMesh()->SetAnim(path::w::DefaultPlayerPath + L"Left\\STAB.png", 2, 0, 0.2f, L"STAB");
	GetMesh()->SetAnim(path::w::DefaultPlayerPath + L"Left\\BOW.png", 3, 0, 0.2f, L"BOW");

	UInput::Instance().EventRegist([this](float) {
		GetMesh()->ChangeAnim(L"SWING1");	 }, EKeyState::Press, DIK_A);

	UInput::Instance().EventRegist([this](float) {
		GetMesh()->ChangeAnim(L"SWING2");	 }, EKeyState::Press, DIK_S);
	
	UInput::Instance().EventRegist([this](float) {
		GetMesh()->ChangeAnim(L"BOW");	 }, EKeyState::Press, DIK_D);
	UInput::Instance().EventRegist([this](float) {
		GetMesh()->ChangeAnim(L"STAB");	 }, EKeyState::Press, DIK_F);

	SetLocation(FVector3 { 0,0,0 });
	SetVelocity(FVector3 { 200,200,10 });

	UInput::Instance().EventRegist([this](float dt) {
		MoveForward(dt);
		}, EKeyState::Hold, DIK_UP);

	using namespace std::placeholders;

	UInput::Instance().EventRegist(std::bind(&APlayer::MoveForward,this,_1), EKeyState::Hold, DIK_UP);
	UInput::Instance().EventRegist(std::bind(&APlayer::MoveBackward, this,_1), EKeyState::Hold, DIK_DOWN);
	UInput::Instance().EventRegist(std::bind(&APlayer::MoveLeft, this,_1), EKeyState::Hold, DIK_LEFT);
	UInput::Instance().EventRegist(std::bind(&APlayer::MoveRight, this,_1), EKeyState::Hold, DIK_RIGHT);

	UInput::Instance().EventRegist([this](float dt) {
		RotateZAxis(FMath::DegreeTORadian(30.f*dt));}, EKeyState::Hold, DIK_E);

	UInput::Instance().EventRegist([this](float dt) {
		RotateZAxis(FMath::DegreeTORadian(-30.f*dt)); }, EKeyState::Hold, DIK_Q);

	UInput::Instance().EventRegist([this](float dt) {
		FVector3 _Scale = GetScale();
		_Scale.x += dt * 1.f;
		SetScale(_Scale); }, EKeyState::Hold, DIK_1);

	UInput::Instance().EventRegist([this](float dt) {
		FVector3 _Scale = GetScale();
		_Scale.y += dt * 1.f;
		SetScale(_Scale); }, EKeyState::Hold, DIK_2);

	UInput::Instance().EventRegist([this](float dt) {
		FVector3 _Scale = GetScale();
		_Scale.y -= dt * 1.f;
		SetScale(_Scale); }, EKeyState::Hold, DIK_3);

	UInput::Instance().EventRegist([this](float dt) {
		FVector3 _Scale = GetScale();
		_Scale.x -= dt * 1.f;
		SetScale(_Scale); }, EKeyState::Hold, DIK_4);
};

bool APlayer::Init()noexcept {
	AActor::Init();
	return true; 
}

bool APlayer::Release() noexcept{
	Super::Release();
	return true;
}

bool APlayer::Frame(float DeltaTime){
	Super::Frame(DeltaTime);
	/*GetMesh()->ConstantData.Time += DeltaTime*0.01;*/
	return true;
}

bool APlayer::Render(float DeltaTime){
	Super::Render(DeltaTime);
	return true;
}


APlayer::~APlayer() noexcept{}

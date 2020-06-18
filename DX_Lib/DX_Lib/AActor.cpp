#include "AActor.h"
#include "helper.h"

#include "UWorld.h"
#include "UCollision.h"
#include "UMesh.h"

bool AActor::Init() noexcept
{
	return true;
};

bool AActor::Release() noexcept
{
	for (auto& Component : ComponentList) {
		if (IsValid(Component) == false) {
			continue;
		};
		Safe_Release(Component);
		Safe_Delete(Component);
	}
	ComponentList.clear();

	UWorld::Instance().ExcludedObject(_Mesh);
	UWorld::Instance().ExcludedObject(_Collision);
	_Mesh = nullptr;
	_Collision = nullptr;

	return true;
};

bool AActor::Frame(float DeltaTime)
{

	return true;
};

bool AActor::Render(float DeltaTime)
{
	
	return true;
};

AActor::~AActor() noexcept
{
	Release();
}

void AActor::SetMesh(class UMesh* Rhs) & noexcept {
	if (IsValid(Rhs)) {
		_Mesh = std::move_if_noexcept(Rhs);
		_Mesh->SetOwner(this);
	};
};

void AActor::MoveForward( float DeltaTime) {
	auto Position = GetLocation();
	Position.y -= Velocity.y * DeltaTime;
	SetLocation(Position);
}
void AActor::MoveBackward( float DeltaTime) {
	auto Position = GetLocation();
	Position.y += Velocity.y * DeltaTime;
	SetLocation(Position);
}
void AActor::MoveRight( float DeltaTime) {
	auto Position = GetLocation();
	Position.x += Velocity.x * DeltaTime;
	SetLocation(Position);
}
void AActor::MoveLeft( float DeltaTime) {
	auto Position = GetLocation();
	Position.x -= Velocity.x * DeltaTime;
	SetLocation(Position);
	
}

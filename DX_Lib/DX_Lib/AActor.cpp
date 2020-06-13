#include "AActor.h"
#include "helper.h"

#include "UMesh.h"

bool AActor::Init() noexcept
{
	return true;
}

bool AActor::Release() noexcept
{
	for (auto& Component : ComponentList) {
		if (IsValid(Component)) {
			Component->Release();
		}
	}
	ComponentList.clear();
	return true;
}

bool AActor::Frame(float DeltaTime )
{
	for (auto& Component : ComponentList) {
		if (IsValid(Component)) {
			Component->Frame(DeltaTime);
		}
		
	}
	return true;
}

bool AActor::Render(float DeltaTime)
{
	for (auto& Component : ComponentList) {
		if (IsValid(Component)) {
			Component->Render(DeltaTime);
		}
	}
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
	}
}

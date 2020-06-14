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
		DX::Safe_Release(Component);
		Safe_Delete(Component);
	}
	ComponentList.clear();
	return true;
}

bool AActor::Frame(float DeltaTime )
{
	
	return true;
}

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

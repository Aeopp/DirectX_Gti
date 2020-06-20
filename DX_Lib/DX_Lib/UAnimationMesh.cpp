#include "UAnimationMesh.h"
#include "helper.h"
#include "UMeshData.h"



bool UAnimationMesh::Frame(float DeltaTime)
{

	return true;
}

bool UAnimationMesh::Render(float DeltaTime)
{
	UMesh::Render(DeltaTime);
	return true;
}

UAnimationMesh::~UAnimationMesh()noexcept {
}


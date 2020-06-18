#include "UAnimationMesh.h"
#include "helper.h"
#include "UMeshData.h"



bool UAnimationMesh::Frame(float DeltaTime)
{
	
	/*CurrentAnimationData.Current_0 = ;
	CurrentAnimationData.Current_1 = ;
	CurrentAnimationData.Current_2 = ;
	CurrentAnimationData.Current_3 = ;

	ConstantData.uvx = CurrentAnimationData.Current_X;
	ConstantData.uvy = CurrentAnimationData.Current_Y;*/
	return true;
}

bool UAnimationMesh::Render(float DeltaTime)
{
	UMesh::Render(DeltaTime);
	return true;
}

UAnimationMesh::~UAnimationMesh()noexcept {
}


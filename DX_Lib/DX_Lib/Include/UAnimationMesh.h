#pragma once
#include "UMesh.h"
#include <map>

class UAnimationMesh  : public UMesh{
public:
	void SetAnim(const std::wstring AnimFileName,
		AnimData AnimationData, std::wstring AnimName)&;
	void ChangeAnim(const std::wstring& AnimFileName)&;
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);
private:
	UAnimationMesh() = default;
	virtual ~UAnimationMesh()noexcept;
	DECLARE_DELETE_MOVE_COPY(UAnimationMesh);
};

// �ʿ��� ���� 1
// �ִϸ��̼� ���
// 


#pragma once
#include "UObject.h"
#include "Declare.h"
#include "DX_Header.h"

#include "Shader.h"
#include "FRect.h"

#include <string_view>
#include <vector>

class UMesh : public UObject
{
public :
	friend class UWorld;

	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DContext = nullptr;

	static constexpr unsigned int VertexNumber = 6;
	std::vector<PCT_VERTEX>		VertexList{};

	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11InputLayout* VertexLayout = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader*  PS = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11SamplerState* SamplerState = nullptr;

	D3D11_SAMPLER_DESC SamplerDESC{};

	class AActor* Owner = nullptr;
	FRect RenderRect{};

	std::vector<ID3D11ShaderResourceView*> AnimSRV;

	uint32_t Layer = 0;
	uint32_t AnimLength = 10;
	float AnimTime = 0.f;
	bool bAnim = false;

	enum class ELayer :uint32_t {
		BackGround=0,
		Character,
		Effect,
		UI,
	};
public :
	inline class AActor* GetOwner() & noexcept {
		return Owner;
	};
	void SetOwner(class AActor* Param) & noexcept;

	bool Create(
		const std::wstring_view pTextureFileName,
		FRect rect, class AActor* Owner,
		const ELayer SetLayer,
		ID3D11Device* pd3dDevice=nullptr,
		ID3D11DeviceContext* pContext=nullptr);
	bool Init()noexcept;
	bool Release()noexcept;
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);
protected:
	virtual bool CreateSamplerDESC()&;
private:
	void OwnerPositionTORenderRECT()&;
private:
	UMesh() = default;
	virtual ~UMesh()noexcept;
	DECLARE_DELETE_MOVE_COPY(UMesh);
};


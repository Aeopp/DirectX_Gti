#pragma once
#include "UObject.h"
#include "Declare.h"
#include "DX_Header.h"

#include "Shader.h"
#include "FRect.h"

#include <string_view>
#include <vector>
#include <map>

// 상수버퍼는 레지스터(float4) 단위로 저장

struct AnimData {
	ID3D11ShaderResourceView* AnimSRV{ nullptr };
	int CurrentFrame{0};
	int AnimLength{ 1};
	float TransitionTime{ 0 };
	float DeltaTime{ 0 };
	~AnimData() noexcept;
};

class UMesh : public UObject
{
public :
	friend class UWorld;

	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DContext = nullptr;
	ID3D11BlendState* AlphaBlend= nullptr;
	ID3D11BlendState* CurrentBlendState = nullptr;
	ID3D11BlendState* DisableBlendState = nullptr;
	ID3D11SamplerState* SamplerState = nullptr;

	//static constexpr unsigned int VertexNumber = 6;
	std::vector<PCT_VERTEX>		VertexList{};
	std::vector<DWORD> IndexList;

	ID3D11Buffer* IndexBuffer = nullptr;
	ID3D11Buffer* ConstantBuffer = nullptr;
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3DBlob* VSBuf{ nullptr };
	ID3D11InputLayout* VertexLayout = nullptr;
	ID3D11VertexShader* VS = nullptr;
	ID3D11PixelShader*  PS = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;

	D3D11_SAMPLER_DESC SamplerDESC{};

	class AActor* Owner = nullptr;
	FRect RenderRect{};
	FVector2 RenderSize{ };
	
	VS_CB ConstantData;

	uint32_t Layer = 0;
	
	AnimData CurrentAnimationData;
	std::map<std::wstring, AnimData> AnimSRVMap;

	enum class ELayer :uint32_t {
		BackGround=0,
		Character,
		Effect,
		UI,
	};

	
public :
	void SetAnim(const std::wstring AnimFileName, int Length, int StartFrame,
		float TransitionTime, std::wstring AnimName)&;;

	void ChangeAnim(const std::wstring& AnimName)&;

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

	virtual void CreateVertexBuffer()&;
	virtual void CreateIndexBuffer()&;
	virtual void CreateConstantBuffer()&;
	virtual void CreateConstantData()&;
	virtual void CreateVertexData()&;
	virtual void CreateIndexData()&;

	void LoadVertexShaderFromFile(const std::wstring_view CompileTargetFilename,
		const std::string_view FunctionName, const std::string_view Profile = "vs_5_0")&;
	void LoadPixelShaderFromFile(const std::wstring_view CompileTargetFilename,
		const std::string_view FunctionName, const std::string_view Profile = "ps_5_0")&;
	void SetInputLayout()&;
protected:
	virtual ~UMesh()noexcept;
	UMesh() = default;
private:
	void OwnerPositionTORenderRECT()&;
private:
	DECLARE_DELETE_MOVE_COPY(UMesh);
};


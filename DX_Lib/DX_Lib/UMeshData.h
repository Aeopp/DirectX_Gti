#pragma once
#include "DX_Header.h"
#include "helper.h"
#include <map>
#include <string>
class UMeshData {
public:
	static inline ID3D11SamplerState* SamplerState = nullptr;
	static inline ID3D11BlendState* BlendState = nullptr;

	static inline ID3D11RasterizerState* RSSolidNone = nullptr;
	static inline ID3D11RasterizerState* RSWireFrameBack = nullptr;
	static inline ID3D11RasterizerState* RSSolidBack = nullptr;
	static inline ID3D11RasterizerState* RSSolidFront = nullptr;

	static inline std::map<std::wstring, ID3D11ShaderResourceView*> ShaderResourceViewMap;
	static ID3D11ShaderResourceView* LoadSRVFromFile(std::wstring pTextureFileName);

	static void ApplySamplerState(ID3D11DeviceContext* Context,
		ID3D11SamplerState* State, UINT SlotNumber = 0, UINT ArrayNumber = 1);;
	static void ApplyBlendState(ID3D11DeviceContext* Context,
		ID3D11BlendState* State,
		const FLOAT BlendFactor[] = 0, UINT Mask = 0xff);
	static void ApplyRastrizerState(ID3D11DeviceContext* Context,
		ID3D11RasterizerState* State);
private:
	static void SetUpRSState();
public:
	static void Create(ID3D11Device* D3DDevice,
		ID3D11DeviceContext* D3DContext)  noexcept;
	static void Release()  noexcept;
	virtual ~UMeshData()noexcept;
	UMeshData() = default;
};

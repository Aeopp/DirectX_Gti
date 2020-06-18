#include "UMeshData.h"
#include "UDevice.h"

ID3D11ShaderResourceView* UMeshData::LoadSRVFromFile(std::wstring pTextureFileName) {
	HRESULT hr;
	ID3D11ShaderResourceView* SRV;

	if (auto iter = ShaderResourceViewMap.find(pTextureFileName);
		iter != std::end(ShaderResourceViewMap)) {
		SRV = iter->second;
	}
	else {
		HRESULT hr =
			D3DX11CreateShaderResourceViewFromFile(
				UDevice::Instance().GetDevice(), pTextureFileName.data(), NULL, NULL,
				&SRV, NULL);

		ShaderResourceViewMap.emplace_hint(iter, std::move(pTextureFileName), SRV);
	};

	return SRV;
};

 void UMeshData::ApplySamplerState(ID3D11DeviceContext* Context, ID3D11SamplerState* State, UINT SlotNumber, UINT ArrayNumber) {
	if (IsValid(Context)) {
		Context->PSSetSamplers(SlotNumber, ArrayNumber, &State);
	};
}

 void UMeshData::ApplyBlendState(ID3D11DeviceContext* Context, ID3D11BlendState* State, const FLOAT BlendFactor[], UINT Mask) {
	if (IsValid(Context)) {
		Context->OMSetBlendState(State, BlendFactor, Mask);
	};
}

 void UMeshData::ApplyRastrizerState(ID3D11DeviceContext* Context, ID3D11RasterizerState* State) {
	if (IsValid(Context)) {
		Context->RSSetState(State);
	}
}

void UMeshData::SetUpRSState()
{
	auto Device = UDevice::Instance().GetDevice();
	auto Context  = UDevice::Instance().GetContext();

	if (!IsValid(Device) || !IsValid(Context)) {
		return; 
	}

	

	{D3D11_RASTERIZER_DESC RSDesc;
	ZeroMemory(&RSDesc, sizeof(RSDesc));
		RSDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		RSDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Device->CreateRasterizerState(&RSDesc, &RSSolidNone);
	}
	
	{D3D11_RASTERIZER_DESC RSDesc;
	ZeroMemory(&RSDesc, sizeof(RSDesc));
		RSDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		RSDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Device->CreateRasterizerState(&RSDesc, &RSSolidFront);
	}

	{D3D11_RASTERIZER_DESC RSDesc;
	ZeroMemory(&RSDesc, sizeof(RSDesc));
		RSDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		RSDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Device->CreateRasterizerState(&RSDesc, &RSSolidBack);
	}

	{D3D11_RASTERIZER_DESC RSDesc;
	ZeroMemory(&RSDesc, sizeof(RSDesc));
		RSDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		RSDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Device->CreateRasterizerState(&RSDesc, &RSWireFrameBack);
	}
}

void UMeshData::Create(ID3D11Device* D3DDevice, ID3D11DeviceContext* D3DContext) noexcept
{
	HRESULT hr;
	// sampler state
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = 1.0f;
	sd.BorderColor[1] = 1.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 1.0f;
	hr = D3DDevice->CreateSamplerState(&sd, &SamplerState);

	// blend state
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(bsd));
	bsd.AlphaToCoverageEnable = FALSE;
	bsd.IndependentBlendEnable= FALSE;
	//BOOL IndependentBlendEnable;
	bsd.RenderTarget[0].BlendEnable = TRUE;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bsd.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = D3DDevice->CreateBlendState(&bsd, &BlendState);

	SetUpRSState();


	if (IsValid(D3DDevice)) {
		UMeshData::ApplyRastrizerState(D3DContext, UMeshData::RSSolidBack);
		UMeshData::ApplyBlendState(D3DContext, UMeshData::BlendState);
		UMeshData::ApplySamplerState(D3DContext, UMeshData::SamplerState);
	}
}

void UMeshData::Release()  noexcept
{
	DX::CheckValidRelease(SamplerState, BlendState, RSSolidNone, RSWireFrameBack,
	RSSolidBack,RSSolidFront);

	for (auto& [key, DeleteResource] : ShaderResourceViewMap) {
		DX::Safe_Release(DeleteResource);
	};
	ShaderResourceViewMap.clear();
}

UMeshData::~UMeshData() noexcept
{
	Release();
}



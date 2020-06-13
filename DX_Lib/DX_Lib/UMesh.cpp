#include "UMesh.h"	
#include "helper.h"
#include "AActor.h"

#include "UDevice.h"
#include "FMath.h"

UMesh::~UMesh()noexcept
{
	Release();
}

bool UMesh::Create(
	const std::wstring_view pTextureFileName,
	FRect rect,
	AActor* Owner, ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext )
{
	if (IsValid(pd3dDevice) == false) {
		pd3dDevice = UDevice::Instance().GetDevice();
	}
	if (IsValid(pContext) == false) {
		pContext = UDevice::Instance().GetContext();
	}

	HRESULT hr;
	D3DDevice = pd3dDevice;
	D3DContext = pContext;
	RenderRect = rect;
	VertexList.resize(6);

	VertexList[0].p = FMath::ScreenToNDC({ rect.left, rect.top });
	VertexList[0].t = FVector2(0, 0);
	
	VertexList[1].p = FMath::ScreenToNDC({ rect.right, rect.top });
	VertexList[1].t = FVector2(1, 0);
	
	VertexList[2].p = FMath::ScreenToNDC({ rect.left, rect.bottom });
	VertexList[2].t = FVector2(0, 1);
	
	VertexList[3].p = FMath::ScreenToNDC({ rect.left, rect.bottom });
	VertexList[3].t = FVector2(0, 1);
	
	VertexList[4].p = FMath::ScreenToNDC({ rect.right, rect.top });
	VertexList[4].t = FVector2(1, 0);
	
	VertexList[5].p = FMath::ScreenToNDC({ rect.right, rect.bottom });
	VertexList[5].t = FVector2(1, 1);

	AnimSRV.resize(AnimLength);

	for (int i = 0; i < 10; i++)
	{
		std::wstring szBuffer = L"..\\..\\..\\Resource\\";
		szBuffer += std::to_wstring(i);
		szBuffer += L".bmp";

		HRESULT hr = D3DX11CreateShaderResourceViewFromFile(D3DDevice, szBuffer.c_str(), NULL, NULL,
			&AnimSRV[i], NULL);

		if (FAILED(hr)) {
			return false; 
		}
	}

	hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pTextureFileName.data(), NULL, NULL,
		&SRV, NULL);

	CreateSamplerDESC();

	hr = D3DDevice->CreateSamplerState(&SamplerDESC, &SamplerState);
		
	if (FAILED(hr)) {
		return false;
	}
	Init();
		//pSamplerDesc.ComparsionFunc=
		//pSamplerDesc.MipLODBias= 
		//이방성 필터링pSamplerDesc.MaxAnisotropy = 16;
	return true;
}

bool UMesh::Init() noexcept
{
	HRESULT hr;

	// 버퍼 정보를 채운다.
	D3D11_BUFFER_DESC bd;

	bd.ByteWidth = sizeof(decltype(VertexList)::value_type) * VertexList.size();
	// 그래픽카드 메모리를 사용
	bd.Usage = D3D11_USAGE_DEFAULT;
	// 버텍스 버퍼에 바인딩
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = VertexList.data();
	// 그래픽카드 메모리에 버퍼를 생성한다
	// bd에 정보가 담겨있고 sd에 해당 버퍼메모리에 채워질 정점 정보가 담겨있다
	// 출력 매개변수 m_pVertexBuffer 로 정점들을 컨트롤 한ㄷ ㅏ . 
	hr = D3DDevice->CreateBuffer(&bd, &sd, &VertexBuffer);
	
		DWORD dwShaderFlags = 0;
		ID3DBlob* VSBuf = nullptr;
		ID3DBlob* ErrorBuf = nullptr;
		hr = D3DX11CompileFromFile(L"VS.hlsl",
			NULL, NULL, "VS", "vs_5_0",
			dwShaderFlags, NULL, NULL, &VSBuf, &ErrorBuf, NULL);

		if (FAILED(hr)) {
			OutputDebugStringA(static_cast<char*>(ErrorBuf->GetBufferPointer()));
		}

		hr = D3DDevice->CreateVertexShader(VSBuf->GetBufferPointer(),VSBuf->GetBufferSize(),NULL,&VS);

		ID3DBlob* PSBuf = nullptr;
		hr = D3DX11CompileFromFile(
			L"PS.hlsl", NULL, NULL,
			"PS","ps_5_0",0, NULL, NULL,&PSBuf, &ErrorBuf, NULL);

		if (FAILED(hr))
		{
			OutputDebugStringA((char*)ErrorBuf->GetBufferPointer());
		}
		hr = D3DDevice->CreatePixelShader(
			PSBuf->GetBufferPointer(),
			PSBuf->GetBufferSize(),
			NULL,
			&PS);
	
	//

	//// 컴파일 오브젝트 파일로부터 버텍스쉐이더를 생성
	//hr = D3DDevice->CreateVertexShader(
	//	Shader::g_VS,
	//	sizeof(Shader::g_VS),
	//	nullptr,
	//	&VS);

	//hr = D3DDevice->CreatePixelShader(
	//	Shader::g_PS,
	//	sizeof(Shader::g_PS),
	//	nullptr,
	//	&PS);

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
		D3D11_INPUT_PER_VERTEX_DATA,0},

		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,
		PCT_VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		PCT_VERTEX::POSITION + PCT_VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	if (layout.empty() == true) {
		// TODO :: layout  이 아직 준비되지 않았다 !!
	};

	hr = D3DDevice->CreateInputLayout(
		layout.data(),
		layout.size(),
		VSBuf->GetBufferPointer(),
		VSBuf->GetBufferSize(),
		&VertexLayout);

	DX::CheckValidRelease(VSBuf, PSBuf, ErrorBuf);

	UINT stride = sizeof(PCT_VERTEX);
	UINT offset = 0;

	if (SRV) {
		D3DContext->PSSetShaderResources(0, 1, &SRV);
	}
	if (SamplerState) {
		D3DContext->PSSetSamplers(0, 1, &SamplerState);
	}

	D3DContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	D3DContext->IASetInputLayout(VertexLayout);
	D3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3DContext->VSSetShader(VS, NULL, 0);
	D3DContext->HSSetShader(NULL, NULL, 0);
	D3DContext->DSSetShader(NULL, NULL, 0);
	D3DContext->GSSetShader(NULL, NULL, 0);
	D3DContext->PSSetShader(PS, NULL, 0);

	if (IsValid(Owner)) {
		SetOwner(Owner);
	}

	return true; 
}

bool UMesh::Release() noexcept
{
	DX::CheckValidRelease(SamplerState,SRV,VertexBuffer,VertexLayout,VS,PS);

	for (auto& SRV : AnimSRV) {
		DX::Safe_Release(SRV);
	};

	return true ;
}

bool UMesh::Frame(float DeltaTime)
{
	if (bAnim) {
		AnimTime = (AnimTime + DeltaTime);
		if (AnimTime >= AnimLength)AnimTime -= static_cast<float>(AnimLength);
	}
	else {

	}
	return true;
}

bool UMesh::Render(float DeltaTime)
{
	// 그리기전에 좌표계 변환
	OwnerPositionTORenderRECT();

	if (bAnim == true) {
		D3DContext->PSSetShaderResources(0, 1,&AnimSRV[static_cast<size_t>(AnimTime)]);
	}
	else {
		D3DContext->PSSetShaderResources(0, 1, &SRV);
	}

	// 갱신된 정점들로 업데이트
	D3DContext->UpdateSubresource(VertexBuffer, 0, NULL, VertexList.data(), 0, 0);

	// 정점 개수와 시작 정점 위치정보를 제공
	D3DContext->Draw(VertexList.size(), 0);

	return true; 
}

bool UMesh::CreateSamplerDESC()&
{
	SamplerDESC.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDESC.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDESC.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDESC.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDESC.MinLOD = 0;
	SamplerDESC.MaxLOD = 0;

	{
		auto& [R, G, B, A] = SamplerDESC.BorderColor;
		R = 0.f;
		G = 0.f;
		B = 0.f;
		A = 1.f;
	}

	return true;
}

void UMesh::OwnerPositionTORenderRECT()&
{
	if (IsValid(Owner) == false) {
		return;
	}

	const FVector3& _Owner_Location = Owner->GetLocation();
	RenderRect.left = _Owner_Location.x;
	RenderRect.top = _Owner_Location.y;

	RenderRect.right = RenderRect.right +_Owner_Location.x;
	RenderRect.bottom = RenderRect.bottom + _Owner_Location.y;

	FVector3 left_top = FMath::ScreenToNDC({ RenderRect.left, RenderRect.top });
	FVector3 right_top = FMath::ScreenToNDC({ RenderRect.right, RenderRect.top });
	FVector3 left_bottom = FMath::ScreenToNDC({ RenderRect.left, RenderRect.bottom });
	FVector3 right_bottom = FMath::ScreenToNDC({ RenderRect.right, RenderRect.bottom });

	VertexList[0].p = left_top;
	VertexList[1].p = right_top;
	VertexList[2].p = left_bottom;
	VertexList[3].p = left_bottom;
	VertexList[4].p = right_top;
	VertexList[5].p = right_bottom;
}


void UMesh::SetOwner(class AActor* Param) & noexcept {
	if (IsValid(Param) == false)return;
	Owner = Param;
};


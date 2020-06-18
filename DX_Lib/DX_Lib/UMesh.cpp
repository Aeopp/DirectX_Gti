#include "helper.h"
#include "AActor.h"

#include "UMesh.h"	
#include "UDevice.h"
#include "FMath.h"
#include "UMeshData.h"
#include "UWindow.h"
#include "UDevice.h"

#include "FVector.h"

#include "helper.h"


UMesh::~UMesh()noexcept{
	Release();
}

bool UMesh::Create(
	const std::wstring_view pTextureFileName,
	FRect rect,
	AActor* Owner, const ELayer SetLayer, 
	ID3D11Device* pd3dDevice,
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
	RenderSize = { RenderRect.right-RenderRect.left,RenderRect.bottom -RenderRect.top};

	CreateVertexData();
	CreateIndexData();
	CreateConstantData();
	
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateConstantBuffer();

	LoadVertexShaderFromFile(L"VS.hlsl", "VS");
	LoadPixelShaderFromFile(L"PS.hlsl", "AlphaBlend");

	SetInputLayout();
	SRV = UMeshData::LoadSRVFromFile(std::wstring(pTextureFileName));

	Layer = static_cast<decltype(Layer)>(SetLayer);

	OwnerPositionTORenderRECT();
	Init();
		//pSamplerDesc.ComparsionFunc=
		//pSamplerDesc.MipLODBias= 
		//이방성 필터링pSamplerDesc.MaxAnisotropy = 16;
	return true;
}

bool UMesh::Init() noexcept
{
	HRESULT hr;

	CreateVertexBuffer();

	SetInputLayout();

	//UINT stride = sizeof(PCT_VERTEX);
	//UINT offset = 0;
	//
	//D3DContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	//D3DContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//D3DContext->IASetInputLayout(VertexLayout);
	//D3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//D3DContext->VSSetShader(VS, NULL, 0);
	//D3DContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	//D3DContext->PSSetConstantBuffers(0, 1,&ConstantBuffer);
	//D3DContext->HSSetShader(NULL, NULL, 0);
	//D3DContext->DSSetShader(NULL, NULL, 0);
	//D3DContext->GSSetShader(NULL, NULL, 0);
	//D3DContext->PSSetShader(PS, NULL, 0);

	//D3DContext->PSSetShaderResources(0, 1, &SRV);

	//D3DContext->PSSetSamplers(0, 1, &SamplerState);
	//D3DContext->OMSetBlendState(CurrentBlendState, 0, 0xffffff);

	if (IsValid(Owner)) {
		SetOwner(Owner);
	}

	return true; 
}

bool UMesh::Release() noexcept
{
	DX::CheckValidRelease(VSBuf,VertexBuffer,VertexLayout,VS,PS,
		IndexBuffer,ConstantBuffer);
	AnimSRVMap.clear();

	return true ;
}

bool UMesh::Frame(float DeltaTime)
{
	VertexList[0].p = FMath::ScreenToNDC({ RenderRect.left, RenderRect.top });
	VertexList[1].p = FMath::ScreenToNDC({ RenderRect.right, RenderRect.top });
	VertexList[2].p = FMath::ScreenToNDC({ RenderRect.left, RenderRect.bottom });
	VertexList[3].p = FMath::ScreenToNDC({ RenderRect.right, RenderRect.bottom });


	//if (bAnim) {
	//	AnimTime = (AnimTime + DeltaTime);
	//	if (AnimTime >= AnimLength)AnimTime -= static_cast<float>(AnimLength);
	//}
	//else {
	//}

	if (auto Owner = GetOwner(); IsValid(Owner)) {
		FRect WindowRect  =UWindow::Instance().GetClientFRect();

		if (auto Owner = GetOwner(); IsValid(Owner)) {
			FVector3 OwnerLocation = Owner->GetLocation();
			OwnerLocation.x /= (WindowRect.right / 2);
			OwnerLocation.y /= (WindowRect.bottom / 2);
			ConstantData.x = OwnerLocation.x;
			ConstantData.y = -OwnerLocation.y;
		}
		/*auto [Owner_x, Owner_y, Owner_z] = Owner->GetLocation();
		auto [_1, _2, ClientWidth, ClientHeight] = UWindow::Instance().GetClientFRect();
		float _Angle = Owner->GetAngle();
		FVector3 OwnerScale = Owner->GetScale();
		auto [Ndc_x, Ndc_y, Ndc_z] = FMath::ScreenToNDC({ Owner_x,Owner_y });
		FVector3 OwnerLoc = Owner->GetLocation();
		auto [Move_X, Move_Y, Move_Z] = FMath::ScreenToNDC({OwnerLoc.x, OwnerLoc.y});
		OwnerLoc.x /= ClientWidth;
		OwnerLoc.y /= ClientHeight;

		ConstantData.x = Move_X;
		ConstantData.y = Move_Y;
		ConstantData.z = Ndc_z;
		ConstantData.Time = DeltaTime;
		ConstantData.angle = _Angle;
		ConstantData.sx = OwnerScale.x;
		ConstantData.sy = OwnerScale.y;
		ConstantData.scx = ClientWidth;
		ConstantData.scx = ClientHeight;*/
	};

	 {
		CurrentAnimationData.DeltaTime += DeltaTime;

		if (CurrentAnimationData.DeltaTime >= CurrentAnimationData.TransitionTime) {
			CurrentAnimationData.DeltaTime -= CurrentAnimationData.TransitionTime;
			++CurrentAnimationData.CurrentFrame;
			CurrentAnimationData.CurrentFrame %=CurrentAnimationData.AnimLength;
		};
		float Temp = 1.f / CurrentAnimationData.AnimLength;

		UMesh::ConstantData.uvtop = Temp * CurrentAnimationData.CurrentFrame;
		UMesh::ConstantData.uvbottom = Temp * (CurrentAnimationData.CurrentFrame+1);
	}
	
	return true;
}

bool UMesh::Render(float DeltaTime)
{
	UINT stride = sizeof(PCT_VERTEX);
	UINT offset = 0;

	D3DContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	D3DContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3DContext->IASetInputLayout(VertexLayout);
	D3DContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3DContext->VSSetShader(VS, NULL, 0);
	D3DContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
	D3DContext->PSSetConstantBuffers(0, 1, &ConstantBuffer);
	D3DContext->HSSetShader(NULL, NULL, 0);
	D3DContext->DSSetShader(NULL, NULL, 0);
	D3DContext->GSSetShader(NULL, NULL, 0);
	D3DContext->PSSetShader(PS, NULL, 0);

	D3DContext->PSSetShaderResources(0, 1, &SRV);
	D3DContext->PSSetSamplers(0, 1, &SamplerState);
	D3DContext->OMSetBlendState(CurrentBlendState, 0, 0xffffff);
	// 그리기전에 좌표계 변환
	OwnerPositionTORenderRECT();
	
	// 갱신된 정점들로 업데이트
	D3DContext->UpdateSubresource(VertexBuffer, 0, NULL, VertexList.data(), 0, 0);
	D3DContext->UpdateSubresource(ConstantBuffer, 0, NULL, &ConstantData, 0, 0);
	// 정점 개수와 시작 정점 위치정보를 제공
	D3DContext->DrawIndexed(IndexList.size(),0,0);

	return true; 
}

void UMesh::CreateVertexBuffer()&
{

	// 버퍼 정보를 채운다.
	D3D11_BUFFER_DESC bd;

	bd.ByteWidth = sizeof(decltype(VertexList)::value_type) * VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = VertexList.data();

	D3DDevice->CreateBuffer(&bd, &sd, &VertexBuffer);
}

void UMesh::CreateIndexBuffer()&
{
	HRESULT hr{};
	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.ByteWidth = sizeof(decltype(IndexList)::value_type) * IndexList.size();;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = IndexList.data();
	hr = D3DDevice->CreateBuffer(&BufferDesc, &sd, &IndexBuffer);
}

void UMesh::CreateConstantBuffer()&
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VS_CB);
	bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = &ConstantData;
	D3DDevice->CreateBuffer(&bd, &sd, &ConstantBuffer);
}

void UMesh::CreateConstantData()&
{
	ConstantData.r = 1.f;
	ConstantData.g = 1.f;
	ConstantData.b = 1.f;
	ConstantData.a = 1.f;
	ConstantData.x = 1.f;
	ConstantData.y = 1.f;
	ConstantData.z = 1.f;
	ConstantData.sx = 1.f;
	ConstantData.sy = 1.f;
	ConstantData.sz = 1.f;
	FVector3 RenderSizeNDC = FMath::ScreenToNDC({ RenderSize });
	
	auto[_1,_2, ClientWindowWidth,ClientWindowHeight]=UWindow::Instance().GetClientFRect();

	RenderSize.x;
	RenderSize.y;

	ConstantData.rsx = 1;
	ConstantData.rsy = 1;
	ConstantData.rsz = 1;
	
	ConstantData.rsx_padding = {1.f};
	ConstantData.Time = {};
}

void UMesh::CreateVertexData()&
{
	VertexList.resize(4);
	VertexList[0].p = FMath::ScreenToNDC({ RenderRect.left, RenderRect.top });
	VertexList[0].c = FVector4(1, 0, 0, 1);
	VertexList[0].t = FVector2(0, 0);

	VertexList[1].p = FMath::ScreenToNDC({ RenderRect.right, RenderRect.top });
	VertexList[1].c = FVector4(0, 1, 0, 1);
	VertexList[1].t = FVector2(1, 0);

	VertexList[2].p = FMath::ScreenToNDC({ RenderRect.left, RenderRect.bottom });
	VertexList[2].c = FVector4(0, 0, 1, 1);
	VertexList[2].t = FVector2(0, 1);

	VertexList[3].p = FMath::ScreenToNDC({ RenderRect.right, RenderRect.bottom });
	VertexList[3].c = FVector4(1, 1, 1, 1);
	VertexList[3].t = FVector2(1, 1);
}

void UMesh::CreateIndexData()&
{
	IndexList.resize(6);
	IndexList[0] = 0;
	IndexList[1] = 1; 
	IndexList[2] = 2;
	IndexList[3] = 2; 
	IndexList[4] = 1; 
	IndexList[5] = 3;
}

void UMesh::LoadVertexShaderFromFile(const std::wstring_view CompileTargetFilename,
	const std::string_view FunctionName, const std::string_view Profile)&
{
	DWORD dwShaderFlags = 0;
	ID3DBlob* ErrorBuf = nullptr;
	HRESULT hr = D3DX11CompileFromFile(CompileTargetFilename.data(),
		NULL, NULL, FunctionName.data()  , Profile.data(),
		dwShaderFlags, NULL, NULL, &VSBuf, &ErrorBuf, NULL);

	if (FAILED(hr)) {
		OutputDebugStringA(static_cast<char*>(ErrorBuf->GetBufferPointer()));
	};

	hr = D3DDevice->CreateVertexShader(VSBuf->GetBufferPointer(), VSBuf->GetBufferSize(), NULL, &VS);

	DX::CheckValidRelease( ErrorBuf);
}

void UMesh::LoadPixelShaderFromFile(const std::wstring_view CompileTargetFilename,
	const std::string_view FunctionName, const std::string_view Profile)&
{
	HRESULT hr;
	ID3DBlob* ErrorBuf = nullptr;
	ID3DBlob* PSBuf = nullptr;

	hr = D3DX11CompileFromFile(
		CompileTargetFilename.data(), NULL, NULL,
		FunctionName.data(), Profile.data(), 0, NULL, NULL, &PSBuf, &ErrorBuf, NULL);

	if (FAILED(hr)){
		OutputDebugStringA((char*)ErrorBuf->GetBufferPointer());
	};

	hr = D3DDevice->CreatePixelShader(
		PSBuf->GetBufferPointer(),
		PSBuf->GetBufferSize(),
		NULL,
		&PS);

	DX::CheckValidRelease(PSBuf, ErrorBuf);
}

void UMesh::SetInputLayout()&
{
	if (IsValid(VSBuf) == false)return;

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
		D3D11_INPUT_PER_VERTEX_DATA,0},

		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,
		PCT_VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		PCT_VERTEX::POSITION + PCT_VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	
	D3DDevice->CreateInputLayout(
	layout.data(),
	layout.size(),
	VSBuf->GetBufferPointer(),
	VSBuf->GetBufferSize(),
	&VertexLayout);
}
void UMesh::OwnerPositionTORenderRECT()&
{
	if (IsValid(Owner) == false) {
		return;
	}
	FVector3 Vec = GetOwner()->GetLocation();
	Vec.x;
	Vec.y;
	
	/*auto OwnerPosition = Owner->GetLocation();

	const FVector3& _Owner_Location = Owner->GetLocation();
	RenderRect.left = _Owner_Location.x;
	RenderRect.top = _Owner_Location.y;

	RenderRect.right = RenderSize.x + _Owner_Location.x;
	RenderRect.bottom = RenderSize.y + _Owner_Location.y;

	FVector3 left_top = FMath::ScreenToNDC({ RenderRect.left, RenderRect.top });
	FVector3 right_top = FMath::ScreenToNDC({ RenderRect.right, RenderRect.top });
	FVector3 left_bottom = FMath::ScreenToNDC({ RenderRect.left, RenderRect.bottom });
	FVector3 right_bottom = FMath::ScreenToNDC({ RenderRect.right, RenderRect.bottom });

	VertexList[0].p = left_top;
	VertexList[1].p = right_top;
	VertexList[2].p = left_bottom;
	VertexList[3].p = right_bottom;*/
};

 void UMesh::SetAnim(const std::wstring AnimFileName, int Length, int StartFrame,
	 float TransitionTime, std::wstring AnimName)& {
	 
	 AnimData AnimationData;
	 AnimationData.AnimLength = Length;
	 AnimationData.CurrentFrame = StartFrame;
	 AnimationData.TransitionTime = TransitionTime;
	 AnimationData.AnimSRV = UMeshData::LoadSRVFromFile(AnimFileName);
	 AnimSRVMap.emplace(std::move(AnimName), AnimationData);
}

 void UMesh::ChangeAnim(const std::wstring& AnimName)& {
	 if (auto iter = AnimSRVMap.find(AnimName);
		 iter != std::end(AnimSRVMap)) {
		 CurrentAnimationData = iter->second;
	 };

	if (IsValid(CurrentAnimationData.AnimSRV)) {
		SRV = CurrentAnimationData.AnimSRV;
	}
}

void UMesh::SetOwner(class AActor* Param) & noexcept {
	if (IsValid(Param) == false)return;
	Owner = Param;
};

 AnimData::~AnimData() noexcept {
	
}

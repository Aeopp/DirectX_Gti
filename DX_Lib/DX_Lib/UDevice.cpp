#include "UDevice.h"
#include "UWindow.h"
#include "helper.h"
#include <cassert>

bool UDevice::SetD3DDevice(const UINT width, const UINT height) &{
	if (CreateDevice() == false) 
		return false;
	if (CreateGIFactory() == false)
		return false;
	if (CreateSwapChain(width,height) == false)
		return false;
	if (CreateRenderTarget() == false)
		return false;
	if (CreateViewport() == false)
		return false;

	return true;
}

bool UDevice::CreateGIFactory()
{
	if (D3DDevice == NULL) {
		return E_FAIL;
	};

	HRESULT HR;
	IDXGIDevice* _DXGIDevice;
	
	HR = D3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&_DXGIDevice);

	if (FAILED(HR)) {
		return false; 
	}

	IDXGIAdapter* _DXGIAdapter;
	HR = _DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&_DXGIAdapter);

	if (FAILED(HR)) {
		return false; 
	}

	HR = _DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&GIFactory);

	if (FAILED(HR)) {
		return false; 
	}

	_DXGIAdapter->Release();
	_DXGIDevice->Release();

	return true;
}

bool UDevice::CreateDevice(){
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef  _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

	HRESULT HR = D3D11CreateDevice(
		NULL,
		DriverType,
		NULL,
		Flags,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&D3DDevice,
		&FeatureLevel,
		&D3DContext);


	if (FAILED(HR)){
		return false;
	}
	return true;
}

bool UDevice::CreateSwapChain(const UINT width, const UINT height)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.OutputWindow = UWindow::Instance().hWnd;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT HR = GIFactory->CreateSwapChain(
		D3DDevice, &sd, &SwapChain);

	if (FAILED(HR)){
		return false;
	}
	return true;
}

bool UDevice::CreateRenderTarget()
{
	ID3D11Texture2D* BackBuffer = nullptr;
	HRESULT hr = SwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&BackBuffer);

	if (FAILED(hr)) {
		return false;
	}

	if (FAILED(D3DDevice->CreateRenderTargetView(
		BackBuffer,
		NULL,
		&RTV))) {
		return false;
	}

	BackBuffer->Release();

	D3DContext->OMSetRenderTargets(1, &RTV, NULL);

	return true;
}

bool UDevice::CreateViewport()
{
	DXGI_SWAP_CHAIN_DESC currentSD;
	SwapChain->GetDesc(&currentSD);
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.Width = currentSD.BufferDesc.Width;
	ViewPort.Height = currentSD.BufferDesc.Height;
	ViewPort.MinDepth = 0;
	ViewPort.MaxDepth = 1;
	D3DContext->RSSetViewports(1, &ViewPort);

	return true; 
}

bool UDevice::ReleaseDevice()
{
	DX::CheckValidRelease(RTV, SwapChain, D3DContext, GIFactory, D3DDevice);

	return true; 
}

void UDevice::DefaultCreateDXResource()&
{
		IDXGISurface* Surface = nullptr;
		UDevice::Instance().SwapChain->GetBuffer
		(0, __uuidof(IDXGISurface), (void**)&Surface); if (Surface) Surface->Release();
}

void UDevice::DefaultDeleteDXResource()&
{
}

void UDevice::DefaultResizeDevice(UINT width, UINT height)&
{
	if (D3DDevice == nullptr)return;

		assert(DeleteDXResource && L"DeleteDXResource SetUp Plz...");
		DeleteDXResource();

		D3DContext->OMSetRenderTargets(0, NULL, NULL);
		if (RTV != nullptr) {
			RTV->Release();
		}

		DXGI_SWAP_CHAIN_DESC currentSD;
		SwapChain->GetDesc(&currentSD);

		HRESULT hr = SwapChain->ResizeBuffers(
			currentSD.BufferCount, width, height,
			currentSD.BufferDesc.Format,
			currentSD.Flags);

		if (FAILED(hr)) {
			return;
		}
		CreateRenderTarget();
		CreateViewport();
		assert(CreateDXResource  && L"CreateDXResource SetUp Plz...");
		CreateDXResource();
}


UDevice::UDevice()  {
}

UDevice::~UDevice()noexcept {
	ReleaseDevice();
}

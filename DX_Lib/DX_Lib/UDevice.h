#pragma once
#include "SingleTon.h"
#include "DX_Header.h"
#include <functional>

using std::placeholders::_1;
using std::placeholders::_2;

class UDevice : public SingleTon<UDevice> 
{
public :
	ID3D11Device* D3DDevice = nullptr;
	ID3D11DeviceContext* D3DContext = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
	IDXGIFactory* GIFactory = nullptr; 
	D3D11_VIEWPORT ViewPort = {};
public :
	inline ID3D11Device* GetDevice()const& {
		return D3DDevice;
	};
	inline ID3D11DeviceContext* GetContext() const& {
		return D3DContext;
	}
public :
	bool SetD3DDevice(const UINT width, const UINT height)&;
	bool CreateGIFactory();
	bool CreateDevice();
	bool CreateSwapChain(const UINT width, const UINT height);
	bool CreateRenderTarget();
	bool CreateViewport();
	bool ReleaseDevice();
	
	// 디바이스 사용자는 DX API 자원 관리 방법을 지정해줄수도 디폴트로 냅둘수도 있다.
	std::function<void() >	         CreateDXResource    { std::bind(&UDevice::DefaultCreateDXResource, this) };
	std::function<void() >	         DeleteDXResource    { std::bind(&UDevice::DefaultDeleteDXResource, this)};
	std::function<void(UINT,UINT)>   ResizeDevice{ std::bind(&UDevice::DefaultResizeDevice,     this, _1, _2)};
private:
	void DefaultCreateDXResource()&;
	void DefaultDeleteDXResource()&;
	void DefaultResizeDevice(UINT width, UINT height)&;
	DECLARE_SINGLETON(UDevice);
};


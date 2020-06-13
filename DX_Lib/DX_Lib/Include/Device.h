#pragma once
#include "SingleTon.h"
#include "DX_Header.h"
#include <functional>
class Device : public SingleTon<Device> 
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

	// 디바이스 사용자는 DX API 자원 관리 방법을 명시해주세요.
	std::function<void() > CreateDXResource{};
	std::function<void() > DeleteDXResource{};
	std::function<void(UINT,UINT)> ResizeDevice{}; 

	DECLARE_SINGLETON(Device);
};


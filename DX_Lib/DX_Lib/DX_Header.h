#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <dxgi.h>

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "DX_Lib.lib")
#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

// DirectX Utility
#if defined(_DEBUG)
#pragma comment (lib, "d3dx11d.lib")
#else
#pragma comment (lib, "d3dx11.lib")
#endif 


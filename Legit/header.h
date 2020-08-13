#pragma once
#include <d3d9.h>
#include <d3dx9.h>


#ifdef _WIN64
#pragma comment(lib, "x64/d3d9.lib")
#pragma comment(lib, "x64/d3dx9.lib")
#else
#pragma comment(lib, "x86/d3d9.lib")
#pragma comment(lib, "x86/d3dx9.lib")
#endif
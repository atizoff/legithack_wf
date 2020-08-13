#include "header.h"
#include "cClasess.h"
#include "cFunction.h"
#include "vmt.h"

typedef HRESULT(WINAPI* PresentSceneFN)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
PresentSceneFN oPresent;


VMTHookManager* VmtHook = new VMTHookManager;

HRESULT WINAPI pPresent(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	function();
	return oPresent(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

void APIENTRY engine()
{
	Sleep(10000);
	Beep(800, 800);

	VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetIRenderer()->m_pDirectDevice);
	oPresent = (PresentSceneFN)VmtHook->dwHookMethod((DWORD64)pPresent, 17);
}


BOOL WINAPI DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(engine), hModule, NULL, NULL);
		break;

	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread(hModule, 0);
		VmtHook->UnHook();
		break;
	}

	return TRUE;
}

#include "header.h"
#include "cClasess.h"
#include "cFunction.h"
#include "vmt.h"

typedef HRESULT(WINAPI* EndSceneFN)(IDirect3DDevice9*);
EndSceneFN oEndScene;

VMTHookManager* VmtHook = new VMTHookManager;

HRESULT WINAPI hkEndScene(IDirect3DDevice9* m_pDevice)
{
	function();
	return oEndScene(m_pDevice);
}

void APIENTRY engine()
{
	Sleep(10000);
	Beep(800, 800);

	VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetIRenderer()->m_pDirectDevice);
	oEndScene = (EndSceneFN)VmtHook->dwHookMethod((DWORD64)hkEndScene, 42);
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

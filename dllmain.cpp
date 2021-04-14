#include "header.h"

typedef INT(WINAPI* m_pUpdate)(ISystem*, INT, INT);
m_pUpdate oUpdate;

VMTHookManager* VmtHook = new VMTHookManager;

INT APIENTRY hkUpdate(ISystem* pSystem, INT iInfo, INT iPause)
{
	function();
	return oUpdate(pSystem, iInfo, iPause);
}

void APIENTRY engine()
{
	Sleep(10000);
	Beep(800, 800);

	VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->GetISystem());
	oUpdate = (m_pUpdate)VmtHook->dwHookMethod((DWORD64)hkUpdate, 4);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(engine), hModule, NULL, NULL);
	}

	else if (dwReason == DLL_PROCESS_DETACH) {
		FreeLibraryAndExitThread(hModule, 0);
		VmtHook->UnHook();
	}

	return TRUE;
}

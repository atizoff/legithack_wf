#pragma once
#include "header.h"
#include "cHelper.h"

class SSystemGlobalEnvironment;
class IGameFramework;
class IGameRules;
class IRenderer;

class IActor;
class IActorSystem;

class IEntity;
class IEntityIt;
class IEntityProxy;
class IEntitySystem;

template <typename t>
t VIRTUAL(PVOID BASE, DWORD64 INDEX)
{
	return (*(t**)BASE)[INDEX];
}

enum IActor_DATA : DWORD64
{
	// -> string -> по имени
	claymore_detector_radius = 0xEA4
};

class SSystemGlobalEnvironment
{
public:
	IRenderer*	   GetIRenderer()	  { return (IRenderer*)    *(DWORD64*)((DWORD64)this + 0x48); } // string -> Draw2DLine ( не помню =( )
	IEntitySystem* GetIEntitySystem() { return (IEntitySystem*)*(DWORD64*)((DWORD64)this + 0xD8); } // string -> GetEntityByName || // string -> GetEntitiesByClass

	static SSystemGlobalEnvironment* Singleton()
	{
		return *(SSystemGlobalEnvironment**)0x141D4CAA0; // string -> ai_CompatibilityMode
	}
};

class IRenderer
{
public:
	DWORD64* GetDirectDevice()
	{
		return (DWORD64*) * (DWORD64*)((DWORD64)this + 0xA6D0); // import -> D3DXCreateTexture -> j_D3DXCreateTexture -> 2 sub
	}
};

class IEntitySystem
{
public:
	IEntityIt* GetEntityIterator()
	{
		return VIRTUAL<IEntityIt* (__thiscall*)(PVOID)>(this, 21)(this); // string -> GetEntitiesByClass
	}
};

class IEntityIt
{
public:
	IEntity* Next()
	{
		return VIRTUAL<IEntity* (__thiscall*)(PVOID)>(this, 6)(this); // string -> GetEntitiesByClass
	}
};

class IEntity
{
public:

	EntityId GetId()
	{
		return VIRTUAL<EntityId(__thiscall*)(PVOID)>(this, 1)(this);
	}

	IEntityProxy* GetProxy(EEntityProxy proxy)
	{
		return VIRTUAL<IEntityProxy* (__thiscall*)(PVOID, EEntityProxy)>(this, 59)(this, proxy); // string -> CreateRenderProxy
	}
};

class IEntityProxy
{
public:

	void SetHUDSilhouettesParams(float a, float r, float g, float b)
	{
		VIRTUAL<void(__thiscall*)(PVOID, float, float, float, float)>(this, 44)(this, a, r, g, b); // string -> HudSilhouettes_Type -> second SUB -> last SUB in pseudocode -> finding offset (COERCE_FLOAT in params)
		m_dwRndFlags |= ESilhouettesParams::eAllMap;
	}

	char pad_0x0000[0x24]; //0x0000
	__int32 m_dwRndFlags; //0x0024
};

class IGameFramework
{
public:
	bool GetClientActor(IActor** pIActor)
	{
		return VIRTUAL<bool(__thiscall*)(PVOID, IActor**)>(this, 142)(this, pIActor); // string -> sp_difficulty -> first SUB
	}

	IActorSystem* GetActorSystem()
	{
		return (IActorSystem*)*(DWORD64*)((DWORD64)this + 0x4E0); // string -> proximityRadius
	}

	IGameRules* GetIGameRules()
	{
		return VIRTUAL<IGameRules* (__thiscall*)(PVOID)>(this, 137)(this); // string -> IsSameTeam
	}

	static IGameFramework* Singleton() { return *(IGameFramework**)0x142056558; } // string -> Failed to create the GameFramework Interface!
};

class IGameRules
{
public:
	INT GetTeam(int entityId)
	{
		return VIRTUAL<INT(__fastcall*)(PVOID, int)>(this, 109)(this, entityId); // string -> IsSameTeam
	}
};

class IActor
{
public:
	IEntity* GetLinkedEntity()
	{
		return (IEntity*)*(DWORD64*)((DWORD64)this + 0x10);
	}

	template <class T>
	inline VOID Set(DWORD64 offset, T value)
	{
		*(T*)((DWORD64)this + offset) = value;
	}
};

class IActorSystem
{
public:
	IActor* GetActor(int entityId)
	{
		return VIRTUAL<IActor* (__thiscall*)(PVOID, int)>(this, 15)(this, entityId);
	}
};


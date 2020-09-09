#pragma once
#include "header.h"
#include "cHelper.h"

class SSystemGlobalEnvironment;
class IGameFramework;
class IGameRules;
class IRenderer;
class ICVar;

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
	// -> string -> by name
	claymore_detector_radius = 0xEA4
};

enum ICVar_DATA : DWORD64
{
	// -> string -> by name
    i_pelletsDisp = 0x12C,
    g_victoryCondition = 0x5F8,
    i_unlimitedammo = 0x134,
    cl_fov = 0x4
};

class SSystemGlobalEnvironment
{
public:
	IRenderer*	   GetIRenderer()	  { return *(IRenderer**)((DWORD64)this + 0x48); } // string -> Draw2DLine ( ? )
	IEntitySystem* GetIEntitySystem() { return *(IEntitySystem**)((DWORD64)this + 0xD8); } // string -> GetEntityByName || // string -> GetEntitiesByClass

	static SSystemGlobalEnvironment* Singleton()
	{
		return *(SSystemGlobalEnvironment**)0x141DB3060; // string -> ai_CompatibilityMode
	}
};

class IRenderer
{
public:
	char pad_0x0000[0xA6D0]; //0x0000
	__int64 m_pDirectDevice; //0xA6D0 // import -> D3DXCreateTexture -> j_D3DXCreateTexture -> 2 sub
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

	IGameRules* GetIGameRules()
	{
		return VIRTUAL<IGameRules* (__thiscall*)(PVOID)>(this, 137)(this); // string -> IsSameTeam
		/* reverse
		  v4 = a4;
		  v5 = a3;
		  v6 = a2;
		  v7 = (*(__int64 (**)(void))(**(_QWORD **)(a1 + 208) + 1096i64))(); <-- 1096 / 8 = 137 (if 64 bit = 8, if 32 bit = 4)
		*/
	}

	char pad_0x0000[0x4E0]; //0x0000
	IActorSystem* m_pActorSystem; //0x04E0 // string -> proximityRadius

	static IGameFramework* Singleton() { return *(IGameFramework**)0x1420BCA78; } // string -> Failed to create the GameFramework Interface!
};

class IGameRules
{
public:
	INT GetTeam(int entityId)
	{
		return VIRTUAL<INT(__fastcall*)(PVOID, int)>(this, 109)(this, entityId); // string -> IsSameTeam
		/* reverse
		///////////////////// step 1
		DWORD2(v8) = 0;
		*(_QWORD *)&v8 = sub_14113E890; <-- here
		if ( v2 )
		{
			v19 = v1;
			v9 = "IsSameTeam";
		///////////////////// step 2
		v7 = (*(__int64 (**)(void))(**(_QWORD **)(a1 + 208) + 1096i64))(); 
		v10 = 2;
		if ( v7 )
			LOBYTE(v11) = sub_141008850(v7, v5, v4); <-- here
		else
			LOBYTE(v11) = 0;
		///////////////////// step 3
		v6 = *(_DWORD *)(qword_1420558B8 + 1536);
		if ( v6 <= 0xB && v6 != 3 )
			return a2 == a3
				|| (*(unsigned int (__fastcall **)(__int64))(*(_QWORD *)v3 + 872i64))(v3) <-- 872 / 8 = 109 (if 64 bit = 8, if 32 bit = 4)
		*/
	}
};

class IActor
{
public:
	template <class T>
	inline VOID Set(DWORD64 offset, T value)
	{
		*(T*)((DWORD64)this + offset) = value;
	}

	char pad_0x0000[0x10]; //0x0000
	IEntity* m_pEntity; //0x0010 
};

class IActorSystem
{
public:
	IActor* GetActor(int entityId)
	{
		return VIRTUAL<IActor* (__thiscall*)(PVOID, int)>(this, 15)(this, entityId);
	}
};

class ICVar
{
public:
	template <class T>
	inline VOID Set(DWORD64 offset, T value)
	{
		*(T*)((DWORD64)this + offset) = value;
	}
	template <class T>
	inline T Get(DWORD64 offset)
	{
		return *(T*)((DWORD64)this + offset);
	}

	static ICVar* Singleton()
	{
		return *(ICVar**)0x1420BBDD0; // string -> IsSameTeam
		/* reverse

			  ///////////////////// step 1
			  DWORD2(v8) = 0;
			  *(_QWORD *)&v8 = sub_14113E890; <-- here
			  if ( v2 )
			  {
				v19 = v1;
				v9 = "IsSameTeam";
			  ///////////////////// step 2
			  v7 = (*(__int64 (**)(void))(**(_QWORD **)(a1 + 208) + 1096i64))();
              v10 = 2;
              if ( v7 )
				LOBYTE(v11) = sub_141008850(v7, v5, v4); <-- here
              else
				LOBYTE(v11) = 0;
			  ///////////////////// step 3
				v3 = a1;
				v4 = a3;
				v5 = a2;
				v6 = *(_DWORD *)(qword_1420558B8 + 1536); <-- end | 0x1420558B8
		*/ 
	}
};

//  https://vk.com/twardowskui - shit paster =(

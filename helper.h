#pragma once

class SSystemGlobalEnvironment;
class IGameFramework;
class IGameRules;
class ISystem;
class ICVar;

class IActor;
class IActorSystem;

class IEntity;
class IEntityIt;
class IEntityProxy;
class IEntitySystem;

typedef unsigned int EntityId;

enum EEntityProxy
{
	ENTITY_PROXY_RENDER,
	ENTITY_PROXY_PHYSICS,
	ENTITY_PROXY_SCRIPT,
	ENTITY_PROXY_AUDIO,
	ENTITY_PROXY_AI,
	ENTITY_PROXY_AREA,
	ENTITY_PROXY_BOIDS,
	ENTITY_PROXY_BOID_OBJECT,
	ENTITY_PROXY_CAMERA,
	ENTITY_PROXY_FLOWGRAPH,
	ENTITY_PROXY_SUBSTITUTION,
	ENTITY_PROXY_TRIGGER,
	ENTITY_PROXY_ROPE,
	ENTITY_PROXY_ENTITYNODE,
	ENTITY_PROXY_USER,
	ENTITY_PROXY_LAST
};

enum ESilhouettesParams : DWORD64
{
	eAllMap = 0x80018,
	eLimitDistance = 0xFFFFFFEF,
	eMin = 0x80000
};

template <typename t>
t VIRTUAL(PVOID BASE, DWORD64 INDEX)
{
	return (*(t**)BASE)[INDEX];
}
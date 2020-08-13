#pragma once
#include "cClasess.h"

bool IsMyTeam(IActor* mIActor, IActor* eIActor)
{
	INT m_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(mIActor->GetLinkedEntity()->GetId());
	INT e_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(eIActor->GetLinkedEntity()->GetId());

	if (m_team != e_team || e_team == 0)
		return true;
	else
		return false;
}

void function()
{
	SSystemGlobalEnvironment* g_pEnv = SSystemGlobalEnvironment::Singleton();
	IActor* m_pActor = nullptr;

	if (IGameFramework* g_pGame = IGameFramework::Singleton())
	{
		if (g_pGame->GetClientActor(&m_pActor))
		{
			m_pActor->Set(IActor_DATA::claymore_detector_radius, 999);


			IEntityIt* pEntityIt = g_pEnv->GetIEntitySystem()->GetEntityIterator();

			while (IEntity* m_pEntity = pEntityIt->Next())
			{
				IEntityProxy* pEntityProxy = m_pEntity->GetProxy(ENTITY_PROXY_RENDER);
				if (!pEntityProxy) continue;

				if (IActor* pActor = g_pGame->GetActorSystem()->GetActor(m_pEntity->GetId()))
				{
					if (!IsMyTeam(m_pActor, pActor)) continue;

					pEntityProxy->SetHUDSilhouettesParams(255, 255, 0, 0);
				}
			}
		}
	}
}
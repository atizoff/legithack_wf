#pragma once

bool IsMyTeam(IActor* mIActor, IActor* eIActor)
{
	INT m_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(mIActor->m_pEntity->GetId());
	INT e_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(eIActor->m_pEntity->GetId());

	if (m_team != e_team || e_team == 0)
		return true;
	else
		return false;
}

void function()
{
	SSystemGlobalEnvironment* g_pEnv = SSystemGlobalEnvironment::Singleton(); // Получаем основной класс, от которого и будем отталкиваться
	IActor* m_pActor = nullptr; // Иницилизируем нашего актора

	if (IGameFramework* g_pGame = IGameFramework::Singleton()) // Получаем дополнительный класс, все классы кроме SSGE нужно проверять на пустоту, ибо как утверждает CRYENGINE, они бывают пустыми
	{
		if (ICVar* g_pCvar = ICVar::Singleton()) // Получаем класс кваров (как правило разные плюшки в виде фова и прочего)
		{
			if (g_pGame->GetClientActor(&m_pActor)) // Наполняем нашего актора
			{
				m_pActor->Set(IActor_DATA::claymore_detector_radius, 999); // Установление видимости мин
				m_pActor->SetRecoilAnimation(0); // Убираем отадчу ( buged ? )

				g_pCvar->Set(ICVar_DATA::i_pelletsDisp, 999.f); // Убираем разброс
				g_pCvar->Set(ICVar_DATA::cl_fov, 90.f); // Фов


				IEntityIt* pEntityIt = g_pEnv->GetIEntitySystem()->GetEntityIterator(); // Получаем entity iterator

				while (IEntity* m_pEntity = pEntityIt->Next()) // Перебираем
				{
					IEntityProxy* pEntityProxy = m_pEntity->GetProxy(ENTITY_PROXY_RENDER); // Прокси для рендера
					if (!pEntityProxy) continue;

					if (IActor* pActor = g_pGame->m_pActorSystem->GetActor(m_pEntity->GetId())) // Нужно смотреть на айди, если вы напишите код вне if`а, то он будет задействовать и объекты
					{
						if (!IsMyTeam(m_pActor, pActor)) continue; // Проверка на команду

						pEntityProxy->SetHUDSilhouettesParams(255, 255, 0, 0); // Устанавливаем силуэт
					}
				}
			}
		}
	}
}

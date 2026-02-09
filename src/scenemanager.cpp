#include "scenemanager.h"

void SceneManager::ChangeScene(std::unique_ptr<Game::Scene> next)
{
    m_pPendScene = std::move(next);
}

void SceneManager::Update(SceneManager& scnm, PlatformSystem& p)
{
    if (m_pPendScene)
    {
        if (m_pCurrScene) 
            m_pCurrScene->OnExit();
        m_pCurrScene = std::move(m_pPendScene);
        m_pCurrScene->OnEnter();
    }

    if (m_pCurrScene)
    {
        m_pCurrScene->Update(scnm, p);
    }
}


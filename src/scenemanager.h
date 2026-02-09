#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "scene.h"

class SceneManager 
{
public:
	/**
	 *
	 */
	void Update(SceneManager& sceneManager, PlatformSystem& platformSystem);

	/**
	 *
	 */
	void ChangeScene(std::unique_ptr<Game::Scene> next);

private:
	std::unique_ptr<Game::Scene> m_pCurrScene; // The current scene shown ingame
	std::unique_ptr<Game::Scene> m_pPendScene; // Pending upcoming scene
};

#endif


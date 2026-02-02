#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <memory>
#include "scene.h"

class SceneManager {
	public:
	void Update(PlatformSystem&);

	private:
	std::shared_ptr<Game::Scene> currcene;
	std::shared_ptr<Game::Scene> prevScene;
};

#endif


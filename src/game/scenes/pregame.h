#ifndef PREGAMESCENE_H
#define PREGAMESCENE_H

#include "../scene.h"

class PregameScene : public Game::Scene
{
public:
	void Update(SceneManager& sceneManager, PlatformSystem& p) override;

	void OnEnter() override;

	void OnExit() override;

};

#endif

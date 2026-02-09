#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "../../scene.h"

class MainMenuScene : public Game::Scene 
{
public:
	/**
	 * \brief 
	 */ 
	void Update(SceneManager& scnm, PlatformSystem& p) override;

	void OnEnter() override;

	void OnExit() override;

private:
	int m_iSelector = 0;

};
#endif


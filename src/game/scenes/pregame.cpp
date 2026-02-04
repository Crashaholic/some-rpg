#include "pregame.h"

#include "../../syswrap.h"
#include "../scenemanager.h"
#include "mainmenu.h"

void PregameScene::Update(SceneManager& scnm, PlatformSystem& p)
{
	if (p.IsKeyPressed('c'))
	{
		scnm.ChangeScene(std::make_unique<MainMenuScene>());
	}
}

void PregameScene::OnEnter()
{
}

void PregameScene::OnExit()
{
}

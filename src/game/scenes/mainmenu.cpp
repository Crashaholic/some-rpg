#include "mainmenu.h"

#include "../../syswrap.h"
#include "../scenemanager.h"
#include "pregame.h"

void MainMenuScene::OnEnter()
{

}

void MainMenuScene::Update(SceneManager& scnm, PlatformSystem& p)
{
	p.DrawAt(static_cast<char>(220), 1, 1);
	p.DrawAt(static_cast<char>(223), 2, 1);
	p.DrawAt(static_cast<char>(223), 3, 1);
	p.DrawAt(static_cast<char>(220), 4, 1);
	p.DrawAt(static_cast<char>(219), 1, 2);
	p.DrawAt(static_cast<char>(219), 1, 3);
	p.DrawAt(static_cast<char>(223), 3, 3);
	p.DrawAt(static_cast<char>(219), 4, 3);
	p.DrawAt(static_cast<char>(223), 1, 4);
	p.DrawAt(static_cast<char>(220), 2, 4);
	p.DrawAt(static_cast<char>(220), 3, 4);
	p.DrawAt(static_cast<char>(223), 4, 4);
	p.DrawString("R E M S P O", 6, 4);

	p.DrawAt('>', 2, 6 + m_iSelector);
	p.DrawString("Start", 3, 6);
	if (p.IsKeyPressed('s'))
	{
		p.DrawAt('s', 0, 2);
	}

	if (p.IsKeyPressed('b'))
	{
		scnm.ChangeScene(std::make_unique<PregameScene>());
	}
}

void MainMenuScene::OnExit()
{

}

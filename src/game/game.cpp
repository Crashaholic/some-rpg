#include "game.h"

#include "../syswrap.h"
#include "scenemanager.h"
#include "scenes/mainmenu.h"

PlatformSystem p = PlatformSystem();
SceneManager scnm = SceneManager();

void Game::G::Splash()
{
	p.SetupDrawing();
	srand(time(NULL));
	scnm.ChangeScene(std::make_unique<MainMenuScene>());
}

void Game::G::Update()
{
	// TODO: come up with new strategy for screen clearing
	p.NewFrame();
	p.ReadInput();
	scnm.Update(scnm, p);
}

void Game::G::Draw()
{
	p.Render();
}

bool Game::G::CheckExit()
{
	if (p.IsKeyPressed('p'))
	{
		return true;
	}
	return false;

}

void Game::G::DoExit()
{
	//TODO: CLEANUP STUFFS

	// THIS LINE IS IMPORTANT!!!
	// DO NOT REMOVE, OR THE GAME WILL NEVER STOP!!!
	running = false;
}

void Game::G::FinalCleanup()
{
	p.ExitGame();
}


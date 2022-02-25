#include "game.h"

void Game::G::Splash()
{
	srand(time(NULL));
	currentGameState = GameState::MAIN_MENU;
}

void Game::G::Update()
{

	PlatformSystem::ReadInput();
	switch (currentGameState)
	{
		case GameState::MAIN_MENU:
			{
				PlatformSystem::DrawAt('G', 0, 0);
				PlatformSystem::DrawAt('r', 1, 0);
				PlatformSystem::DrawAt('e', 2, 0);
				PlatformSystem::DrawAt('m', 3, 0);
				PlatformSystem::DrawAt('s', 4, 0);
				PlatformSystem::DrawAt('p', 5, 0);
				PlatformSystem::DrawAt('o', 6, 0);

				PlatformSystem::DrawString("abcdef", 0, 3);
				break;
			}
		default:
			break;
	}


}

void Game::G::Draw()
{
	PlatformSystem::Render();
}

bool Game::G::CheckExit()
{
	if (PlatformSystem::IsKeyPressed('p'))
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
	PlatformSystem::ExitGame();
}


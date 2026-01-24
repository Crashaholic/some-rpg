#include "game.h"

PlatformSystem& p = PlatformSystem::Get();

void Game::G::Splash()
{
	srand(time(NULL));
	currentGameState = GameState::MAIN_MENU;
}

void Game::G::Update()
{

	p.ReadInput();
	switch (currentGameState)
	{
		case GameState::MAIN_MENU:
			{
				p.DrawAt(220, 1, 1);
				p.DrawAt(223, 2, 1);
				p.DrawAt(223, 3, 1);
				p.DrawAt(220, 4, 1);
				p.DrawAt(219, 1, 2);
				p.DrawAt(219, 1, 3);
				p.DrawAt(223, 3, 3);
				p.DrawAt(219, 4, 3);
				p.DrawAt(223, 1, 4);
				p.DrawAt(220, 2, 4);
				p.DrawAt(220, 3, 4);
				p.DrawAt(223, 4, 4);
				p.DrawString("R E M S P O", 6, 4);

				p.DrawString("Start", 1, 6);
				if (p.IsKeyPressed('a'))
				{
					p.DrawAt('a', 0, 2);
				}
				break;
			}
		default:
			break;
	}


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


#include "game.h"



int main(int argc, char** args)
{
	PlatformSystem::SetupDrawing();
	Game::G::Get().Splash();
	while (Game::G::Get().running)
	{
		Game::G::Get().Update();
		Game::G::Get().Draw();
		//Game::GetInput(); // TODO: FIX THIS
		if (Game::G::Get().CheckExit())
			Game::G::Get().DoExit();
	}

	Game::G::Get().FinalCleanup();
}


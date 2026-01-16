#include "game/game.h"

using Game::G;

int main(int argc, char** args)
{
	PlatformSystem::Get().SetupDrawing();
	G::Get().Splash();
	while (G::Get().running)
	{
		G::Get().Update();
		G::Get().Draw();
		if (G::Get().CheckExit())
			G::Get().DoExit();
	}

	G::Get().FinalCleanup();
}


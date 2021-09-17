#include "game.h"



int main(int argc, char** args)
{
	PlatformSystem::SetupDrawing();
	Game::Splash();
	while (Game::running)
	{
		Game::Update();
		Game::Draw();
		//Game::GetInput(); // TODO: FIX THIS
		if (Game::CheckExit())
			Game::DoExit();
	}

	Game::FinalCleanup();
}


#ifndef GAME_H
#define GAME_H
#include "syswrap.h"
#include "game/entity.h"
#include "game/biome.h"
#include "gamepackage.h"

namespace Game
{
	bool running = true;

	enum class GameState
	{
		MAIN_MENU,
		MAIN_MENU_NEW_GAME,
		MAIN_MENU_LOAD_GAME,

		GAME,
		GAME_INTRO_SEQUENCE,
		GAME_LOOP,
		// there is no end muahahaha
	} currentGameState ;

	void Splash()
	{
		srand(time(NULL));
		currentGameState = GameState::MAIN_MENU;
	}

	void Update()
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
				break;
			}
			default:
				break;
		}
	}

	/**
	* This will draw the things queued to draw.
	*/
	void Draw()
	{
		PlatformSystem::Render();
	}

	bool isLeavingGame = false;

    // exists to prevent any form of unwanted exits!
	bool CheckExit()
	{
	    if (PlatformSystem::IsKeyPressed('p'))
        {
            return true;
        }
        return false;
	}

	void DoExit()
	{
		//TODO: CLEANUP STUFFS

		// THIS LINE IS IMPORTANT!!!
		// DO NOT REMOVE, OR THE GAME WILL NEVER STOP!!!
		running = false;


		//printf("Quitting...\n");

	}

	void FinalCleanup()
	{
	    PlatformSystem::ExitGame();
	}
}


#endif // GAME_H


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
				PlatformSystem::DrawAt('a', 1, 1);
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
        #if defined(PLATFORM_LINUX)
                endwin();
        #elif defined(PLATFORM_WINDOWS)

        #endif
	}
}


#endif // GAME_H


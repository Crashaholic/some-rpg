#ifndef GAME_H
#define GAME_H
#include "../syswrap.h"
//#include "game/entity.h"
//#include "game/biome.h"
//#include "gamepackage.h"

namespace Game
{
	class G
	{
		G() : currentGameState(GameState::MAIN_MENU) {}
		G(const G& copy) = delete;
		G operator=(const G& copy) = delete;

		public:
		static G& Get()
		{
			static G g;
			return g;
		}

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
		};

		GameState currentGameState;

		void Splash();
		void Update();

		/**
		 * This will draw the things queued to draw.
		 */
		void Draw();
		bool isLeavingGame = false;

		// exists to prevent any form of unwanted exits!
		bool CheckExit();

		void DoExit();

		void FinalCleanup();

	};

}
#endif // GAME_H


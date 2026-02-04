#ifndef GAME_H
#define GAME_H

namespace Game
{
	class G
	{
		public:
		G() 
		: currentGameState(GameState::MAIN_MENU) 
		{

		}


		/**
		 * 
		 */
		enum class GameState
		{
			NONE, 

			MAIN_MENU,
			MAIN_MENU_NEW_GAME,
			MAIN_MENU_LOAD_GAME,

			GAME,
			GAME_INTRO_SEQUENCE,
			GAME_LOOP,
			// there is no end muahahaha
		};


		/**
		 *  \brief 
		 */
		void Splash();
		
		/**
		 *  \brief
		 */
		void Update();

		/**
		 *  \brief This will draw the things queued to draw.
		 */
		void Draw();

		/** 
		 *  \brief Check if the game is to exit.
		 *	\return True if game is going to exit. False if not. 
		 */
		bool CheckExit();

		/**
		 *  \brief
		 */
		void DoExit();

		/**
		 *  \brief 
		 */
		void FinalCleanup();



		/// \brief 
		bool isLeavingGame = false;
		
		/// \brief
		bool running = true;

		/// \brief 
		GameState currentGameState = GameState::NONE;
	};

}
#endif // GAME_H


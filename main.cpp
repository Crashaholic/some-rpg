#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <random>
#include <ctime>
#include <filesystem>
#include <unordered_map>

#if defined(__unix__)
// ncurses reference: https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html
// ref: 
//		https://www.linuxjournal.com/content/creating-adventure-game-terminal-ncurses
//		https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/

#define PLATFORM_LINUX
#include <ncurses.h>
#include <curses.h>

#elif defined(_WIN32)
// ref and/or src: 
//		https://www.randygaul.net/2012/07/03/windows-console-game-asciiengine/

#define PLATFORM_WINDOWS
#include <windows.h>
#include <conio.h>
HANDLE wHnd;
HANDLE rHnd;

#endif

using std::string;
namespace fs = std::filesystem;
using fs::path;

// GLOBAL VALUES, DO NOT MODIFY UNLESS NEEDED
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 35

namespace System
{

#if defined(PLATFORM_LINUX)

#elif defined(PLATFORM_WINDOWS)
	SMALL_RECT windowSize = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	COORD bufferSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	COORD characterBufferSize = { WINDOW_WIDTH, WINDOW_HEIGHT };
	COORD characterPosition = { 0, 0 };
	SMALL_RECT consoleWriteArea = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	/* A CHAR_INFO structure containing data about a single character */
	CHAR_INFO consoleBuffer[WINDOW_WIDTH * WINDOW_HEIGHT];

	INPUT_RECORD* eventBuffer;

	/* Read console input buffer and return malloc'd INPUT_RECORD array */
	DWORD GetInput(INPUT_RECORD** eventBuffer)
	{
		/* Variable for holding the number of current events, and a point to it */
		DWORD numEvents = 0;

		/* Variable for holding how many events were read */
		DWORD numEventsRead = 0;

		/* Put the number of console input events into numEvents */
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);

		if (numEvents) /* if there's an event */
		{
			/* Allocate the correct amount of memory to store the events */
			*eventBuffer = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * numEvents);
			/* Place the stored events into the eventBuffer pointer */
			ReadConsoleInput(rHnd, *eventBuffer, numEvents, &numEventsRead);
		}
		/* Return the amount of events successfully read */
		return numEventsRead;
}

#endif

	void SetupDrawing()
	{
		#if defined(PLATFORM_LINUX)
			initscr();
			raw();
			keypad(stdscr, TRUE);
			noecho();

			// TODO: SETUP AN NCURSES WINDOW WITH WINDOW_WIDTH AND WINDOW_HEIGHT

		#elif defined(PLATFORM_WINDOWS)
			wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
			rHnd = GetStdHandle(STD_INPUT_HANDLE);
			SetConsoleTitle(TEXT("some-rpg"));

			/* Set the window size */
			SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
			/* Set the screen's buffer size */
			SetConsoleScreenBufferSize(wHnd, bufferSize);

			//for (int y = 0; y < WINDOW_HEIGHT; ++y)
			//{
			//	for (int x = 0; x < WINDOW_WIDTH; ++x)
			//	{
			//		consoleBuffer[x + WINDOW_WIDTH * y].Char.AsciiChar = (unsigned char)219;
			//		consoleBuffer[x + WINDOW_WIDTH * y].Attributes = rand() % 256;
			//	}
			//}


			/* Write our character buffer (a single character currently) to the console buffer */
			//WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);

		#endif
	}

	void MoveCursor(int x, int y)
	{

	}

	void DrawAt(char chToDraw, int x, int y)
	{
		#if defined(PLATFORM_LINUX)
			// use ncurses to compile and draw

		#elif defined(PLATFORM_WINDOWS)
			// use WIN API to compile and draw
			//MoveCursor(x, y);
			consoleBuffer[x + WINDOW_WIDTH * y].Char.AsciiChar = chToDraw;
		#endif
	}

	void DrawString(string st, int x, int y)
	{
	}

	#if defined(PLATFORM_LINUX)
	#elif defined(PLATFORM_WINDOWS)
		std::unordered_map<WORD, bool> windowsKeyMapOldFrame;
		std::unordered_map<WORD, bool> windowsKeyMapNewFrame;
	#endif

	void ReadInput()
	{
		#if defined(PLATFORM_LINUX)
			int ch;
			ch = getch();
		#elif defined(PLATFORM_WINDOWS)
			DWORD numEventsRead = GetInput(&eventBuffer);

			if (numEventsRead)
			{
				for (int i = 0; i < numEventsRead; ++i)
				{
					if (eventBuffer[i].EventType == KEY_EVENT)
					{
						windowsKeyMapNewFrame[eventBuffer[i].Event.KeyEvent.wVirtualKeyCode] = eventBuffer[i].Event.KeyEvent.bKeyDown;
					}
				}
				free(eventBuffer);
			}
		#endif

	}

	void Render()
	{
		#if defined(PLATFORM_LINUX)
			refresh();
		#elif defined(PLATFORM_WINDOWS)
			WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		#endif
	}

	void IsKeyPressed()
	{
	}

	void EndFrame()
	{
#if defined(PLATFORM_LINUX)
#elif defined(PLATFORM_WINDOWS)

#endif
	}
}

namespace Game
{
	// semi soft-coding the directories, might be useful?

	path dataDirectory = "data";

	path dataFragmentBiomes = "biome";
	path dataFragmentEntities = "entity";
	path dataFragmentExtras = "extras";
	path dataFragmentAddons = "extras";

	path dataBiomes = dataDirectory / dataFragmentBiomes;
	path dataEntities = dataDirectory / dataFragmentEntities;
	path dataExtras = dataDirectory / dataFragmentExtras;
	path dataAddons = dataDirectory / dataFragmentAddons;

	bool running = true;
	typedef string UID;
	// Generates only 7 characters, should have a low chance of collision
	UID UIDGenPart()
	{
		string tmp = "";
		for (int i = 0; i < 7; ++i)
		{
			int temp = rand() % 62;
			if (temp > 51)
			{
				tmp += '0' + temp - 52;
			}
			else if (temp > 25)
			{
				tmp += 'a' + temp - 26;
			}
			else
			{
				tmp += 'A' + temp;
			}
		}
		return tmp;
	}

	UID UIDGen()
	{
		string part1, part2, part3;
		part1 = UIDGenPart();
		part2 = UIDGenPart();
		part3 = UIDGenPart();
		string temp = 
			part1 + '-' + 
			part2 + '-' + 
			part3;
		return temp;
	}

	struct Serializable
	{
		virtual void WriteToFile(string fileName) = 0;
		virtual void ReadFromFile(string fileName) = 0;
	};


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

	struct StatusEffect : Serializable
	{
		string effectName;
		string effectDesc;
		enum class EffectType { BUFF, DEBUFF, NEUTRAL };
		EffectType effectType;
		int effectDur;

		void WriteToFile(string fileName) override
		{
		}

		void ReadFromFile(string fileName) override
		{
		}

	};

	struct Ability
	{
		enum class Type { ATTACK, DEFENCE, PASSIVE } aType;
		enum class Element { PHYS, FIRE, COLD, HEAL, } element;
		bool singleTarget = false;
		string name;
		string desc;
	};

	struct Behaviour
	{
		// Behaviour dictates what choices an enitity will make.
		enum class BehaviourType { PASSIVE, AGGRESSIVE, AFRAID /*for the "rare monsters ig"*/, SUPPORTIVE };
		BehaviourType bType = BehaviourType::PASSIVE;
	};

	struct BehaviourController
	{
		Behaviour currentBehaviour;
	};

	template <typename T>
	struct StatModifier
	{
		UID modId;
		T value;
		string desc;
		string miniDesc;
		StatModifier()
			: modId("invalid")
		{
		}

		void Instantiate(T val, string des, string mini)
		{
			value = val;
			desc = des;
			miniDesc = mini;
			modId = UIDGen();
		}

		bool CheckValid()
		{
			return modId == "invalid";
		}

		bool operator== (StatModifier& rhs) const
		{
			return modId == rhs.modId;
		}

	};

	template <typename T>
	struct Stat : Serializable
	{
		T rawCurrent;
		T maximum;
		std::vector<StatModifier<T>> modifiers;
		
		Stat(T dValue, T mValue)
		{
			rawCurrent = dValue;
			maximum = mValue;
		}

		Stat()
		{
		}

		StatModifier<T> FindModifierByUID(UID comp)
		{
			for (int i = 0; i < modifiers.size(); ++i)
			{
				if (modifiers[i].modId == comp)
				{
					return modifiers[i];
				}
			}

			return new StatModifier<T>();
		}

		void WriteToFile(string fileName) override
		{
			
		}

		void ReadFromFile(string fileName) override
		{
			
		}
	};

	struct Entity
	{
		string name;

		Stat<int> strn = Stat<int>(0, 50);
		Stat<int> intl = Stat<int>(0, 50);
		Stat<int> dext = Stat<int>(0, 50);
		Stat<int> agil = Stat<int>(0, 50);
		Stat<int> luck = Stat<int>(0, 50);

		Stat<float> hp = Stat<float>(0, 9999); // hit points
		Stat<float> sp = Stat<float>(0, 9999); // shield points
		Stat<float> mp = Stat<float>(0, 9999); // mana points

		Entity()
			: name("undefined")
		{
		}
	};

	struct Player : Entity
	{
	};

	Player currentPlayer;

	struct Item : Serializable
	{
		virtual void ModifyStats() = 0;
		void WriteToFile(string fileName) override
		{
		}

		void ReadFromFile(string fileName) override
		{
		}
	};

	struct Biome : Serializable
	{
		string biomeName;
		int biomeLevel;

		std::vector<Entity> spawnables; // PLACEHOLDER!! DO NOT USE!!

		void WriteToFile(string fileName) override
		{

		}

		void ReadFromFile(string fileName) override
		{
		}
	};

	void LoadBiomesData()
	{
		
	}

	void LoadBiome()
	{
		
	}

	// TODO: get rid of this
	// replace with ncurses variant
	string playerInput;
	string GetInput()
	{
		char temp[512] = "\0";
		//std::getline(std::cin, temp);
#if defined(PLATFORM_LINUX)

#elif defined(PLATFORM_WINDOWS)
		
#endif
		playerInput = temp;
		return playerInput;
	}

	void Splash()
	{
		srand(time(NULL));
		currentGameState = GameState::MAIN_MENU;
	}

	string temp;

	void Update()
	{
		switch (currentGameState)
		{
			case GameState::MAIN_MENU:
			{
				//temp += System::ReadInput();
				System::DrawAt('a', 0, 0);
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
		System::Render();
	}

	bool isLeavingGame = false;

	bool CheckExit()
	{
		return playerInput == "exit";
	}

	void DoExit()
	{
		//TODO:
		//CLEANUP STUFFS

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

int main(int argc, char** args)
{
	int ch;
	System::SetupDrawing();
	Game::Splash();
	while (Game::running)
	{
		Game::Update();
		Game::Draw();
		Game::GetInput();
		if (Game::CheckExit()) 
			Game::DoExit();
	}

	Game::FinalCleanup();
}


#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <random>
#include <ctime>

using std::string;

namespace Game
{
	string dataDirectory = "data";

	string dataBiomes = "biome";
	string dataEntities = "entity";


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
		string part1, part2, part3, part4, part5;
		part1 = UIDGenPart();
		part2 = UIDGenPart();
		part3 = UIDGenPart();
		part4 = UIDGenPart();
		part5 = UIDGenPart();
		string temp = 
			part1 + '-' + 
			part2 + '-' + 
			part3;
		return temp;
	}

	struct Serializable
	{
		virtual void WriteToFile() = 0;
		virtual void ReadFromFile() = 0;
	};

	bool running = true;

	enum GameState
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
		enum EffectType
		{
			BUFF,
			DEBUFF,
			NEUTRAL
		};
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
		enum Type
		{
			ATTACK,
			DEFENCE,
			PASSIVE
		};

		enum Element
		{
			FIRE,
			COLD,
			SHOCK,
			EARTH
		};
		bool singleTarget = false;
		Element element;
		string name;
	};

	struct Behaviour
	{
		// Behaviour dictates what choices an enitity will make.
		enum BehaviourType
		{
			PASSIVE,
			AGGRESSIVE,
			SUPPORTIVE
		};
	};

	struct BehaviourController
	{

	};

	template <typename T>
	struct StatModifier
	{
		uint32_t modId;
		T amount;
	};

	template <typename T>
	struct Stat : Serializable
	{
		T rawCurrent;
		T maximum;
		std::vector<StatModifier<T>> modifiers;

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

		Stat<int> strn;
		Stat<int> intl;
		Stat<int> dext;
		Stat<int> agil;
		Stat<int> luck;

		Stat<float> hp; // hit points
		Stat<float> sp; // shield points
		Stat<float> mp; // mana points

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

	string playerInput;
	string GetInput()
	{
		string temp = "";
		while (temp.empty())
		{
			std::getline(std::cin, temp);
		}
		playerInput = temp;
		return playerInput;
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


		printf("Quitting...\n");

	}

	void Splash()
	{
		srand(time(NULL));
		std::cout
		<< "\t\t#======#\n"
		<< "\t\t# Game #\n"
		<< "\t\t#======#\n\n\n";

		currentGameState = MAIN_MENU;
	}

	void Update()
	{
		switch (currentGameState)
		{
				case MAIN_MENU:
						{
							printf("");

							break;
						}
				default:
						break;
		}
	}
}

int main(int argc, char** args)
{
	Game::Splash();

	// TODO: 
	// --- SHIFT THIS TO THE NEW GAME OPTION ---
	if (argc > 1)
	{
		Game::currentPlayer.name = args[1];
	}
	else
	{
		std::cout << "Enter your name...\n";
		Game::currentPlayer.name = Game::GetInput();
	}

	printf("\n\n\nYour name is... %s\n", Game::currentPlayer.name.c_str());
	// --- TO HERE ---

	printf("Game is running now!\nAwaiting input...\n");
	while (Game::running)
	{
		Game::Update();
		Game::GetInput();
		if (Game::CheckExit()) 
		{
			Game::DoExit();
		}
	}
}


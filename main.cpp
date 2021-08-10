#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <fstream>

using std::string;

namespace Game
{
	string dataDirectory = "/data/";

	bool running = true;

	enum GameState
	{
		MAIN_MENU,
		MAIN_MENU_NEW_GAME,
		MAIN_MENU_LOAD_GAME,


		GAME,
	};

	GameState currentGameState;

	struct StatusEffect
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
	struct Stat
	{
		T rawCurrent;
		T maximum;
		std::vector<StatModifier<T>> modifiers;
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

	struct Item
	{
		virtual void ModifyStats() = 0;
	};

	struct Biome
	{
		string biomeName;
		int biomeLevel;

		std::vector<Entity> spawnables; // PLACEHOLDER!! DO NOT USE!!
	};

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
		std::cout
		<< "\t\t#======#\n"
		<< "\t\t# Game #\n"
		<< "\t\t#======#\n\n\n";
	}

	void Update()
	{
		printf("Game is running now!\nAwaiting input...\n");
		// if (state)
		// {
		// 	Game::StateUpdate();
		// }
	}

	void LoadBiomesData()
	{

	}

	void LoadBiome()
	{

	}
}

int main(int argc, char** args)
{
	Game::Splash();

	// TODO: SHIFT THIS TO THE NEW GAME OPTION
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
	// TO HERE

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


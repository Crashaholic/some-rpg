#ifndef BIOME_H
#define BIOME_H

#include "entity.h"

namespace Game
{
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

}

#endif // BIOME_H

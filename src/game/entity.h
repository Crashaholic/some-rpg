#ifndef ENTITY_H
#define ENTITY_H
#include "stat.h"

namespace Game
{
	struct Entity
	{
		string name;

		Stat<int> strn = Stat<int>("Strength", 0, 50);
		Stat<int> intl = Stat<int>("Intelligence", 0, 50);
		Stat<int> dext = Stat<int>("Dexterity", 0, 50);
		Stat<int> agil = Stat<int>("Agility", 0, 50);
		Stat<int> luck = Stat<int>("Luck", 0, 50);

		Stat<float> hp = Stat<float>("HP", 0, 9999); // hit points
		Stat<float> sp = Stat<float>("SH", 0, 9999); // shield points
		Stat<float> mp = Stat<float>("MP", 0, 9999); // mana points

		Entity()
			: name("undefined")
		{
		}
	};
}
#endif

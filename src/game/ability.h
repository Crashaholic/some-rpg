#ifndef ABILITY_H
#define ABILITY_H

namespace Game
{
	struct Ability
	{
		enum class Type { ATTACK, DEFENCE, PASSIVE } aType;
		enum class Element { PHYS, FIRE, COLD, HEAL, } element;
		bool singleTarget = false;
		string name;
		string desc;
	};
}
#endif // ABILITY_H

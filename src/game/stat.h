#ifndef STAT_H
#define STAT_H
#include "serializable.h"

namespace Game
{
    template <typename T>
	struct Stat : Serializing::Serializable
	{
		T rawCurrent;
		T maximum;
		string name;
		//std::vector<StatModifier<T>> modifiers;

		Stat(string statName, T dValue, T mValue)
		{
		    name = statName;
			rawCurrent = dValue;
			maximum = mValue;
		}

		Stat()
		{
		}

		/*StatModifier<T> FindModifierByUID(UID comp)
		{
			for (int i = 0; i < modifiers.size(); ++i)
			{
				if (modifiers[i].modId == comp)
				{
					return modifiers[i];
				}
			}

			return new StatModifier<T>();
		}*/

		void WriteToFile(string fileName) override
		{

		}

		void ReadFromFile(string fileName) override
		{

		}
	};

}
#endif

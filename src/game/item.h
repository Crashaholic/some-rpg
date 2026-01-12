#ifndef ITEM_H
#define ITEM_H
#include "serializable.h"
namespace Game
{
	struct Item : Serializing::Serializable
	{
		virtual void ModifyStats() = 0;
		void WriteToFile(string fileName) override
		{
		}

		void ReadFromFile(string fileName) override
		{
		}
	};
}
#endif // ITEM_H



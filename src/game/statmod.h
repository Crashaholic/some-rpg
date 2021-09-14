#include "uidgen.h"

namespace Game
{
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
			modId = UIDGen(); // if mod id is not genned, its invalid regardless of data
		}

		bool CheckValid()
		{
			return modId != "invalid";
		}

		bool operator== (StatModifier& rhs) const
		{
			return modId == rhs.modId;
		}

	};

}

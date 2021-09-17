#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

namespace Game
{
	struct Behaviour
	{
		// Behaviour dictates what choices an enitity will make.
		enum class BehaviourType { PASSIVE, AGGRESSIVE, AFRAID /*for the "rare monsters ig"*/, SUPPORTIVE };
		BehaviourType bType = BehaviourType::PASSIVE;
	};

}
#endif // BEHAVIOUR_H

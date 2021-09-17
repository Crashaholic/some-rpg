
#ifndef STATUSFX_H
#define STATUSFX_H

namespace Game
{
	struct StatusEffect
	{
		string effectName;
		string effectDesc;
		enum class EffectType { BUFF, DEBUFF, NEUTRAL };
		EffectType effectType;
		int effectDur;
	};
}

#endif // STATUSFX_H

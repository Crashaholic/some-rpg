#ifndef SCENE_H
#define SCENE_H

// #include "../syswrap.h"
#include <string>

// forward declare PlatformSystem
class PlatformSystem;

namespace Game 
{
	class Scene 
	{
	public:
		virtual void Update(PlatformSystem& p) = 0;

		virtual void OnEnter() = 0;

		virtual void OnExit() = 0;
	};
}

#endif

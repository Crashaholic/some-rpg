#ifndef SCENE_H
#define SCENE_H

// #include "../syswrap.h"
#include <string>

// forward declare PlatformSystem
class PlatformSystem;
// and SceneManager
class SceneManager;

namespace Game 
{
	class Scene 
	{
	public:
		virtual ~Scene() = default;

		virtual void Update(SceneManager& sceneManager, PlatformSystem& p) = 0;

		virtual void OnEnter() = 0;

		virtual void OnExit() = 0;
	};
}

#endif

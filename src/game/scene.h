#ifndef SCENE_H
#define SCENE_H

#include "../syswrap.h"
#include <string>

namespace Game 
{
	class Scene 
	{
	public:
		virtual void Update() = 0;
		// virtual void Draw() = 0;
		std::string sceneChangeRequest;
	};
}

#endif
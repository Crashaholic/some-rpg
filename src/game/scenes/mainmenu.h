#pragma once

#include "../scene.h"
#include "../scenes.h"

namespace Game 
{
	class Scene_MainMenu : public Scene 
	{

	public:
		void Update() override;
		// void Draw() override;
	private:
		int m_iSelector;

	};
}


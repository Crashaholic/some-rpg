#pragma once

#include "../scene.h"
#include "../scenes.h"

namespace Game 
{
	class Scene_MainMenu : public Scene 
	{

	public:
		/// @brief 
		void Update(PlatformSystem& p) override;
		// void Draw() override;
	private:
		int m_iSelector;

	};
}


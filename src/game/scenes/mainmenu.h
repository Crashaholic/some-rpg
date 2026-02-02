#pragma once

#include "../scene.h"

namespace Game 
{
	class MainMenuScene : public Scene 
	{

	public:
		/// @brief 
		void Update(PlatformSystem& p) override;
		// void Draw() override;
	private:
		int m_iSelector;

	};
}


#include "game/game.h"

using Game::G;

int main(int argc, char** args)
{
	Game::G g;
	g.Splash();
	while (g.running)
	{
		g.Update();
		g.Draw();
		if (g.CheckExit())
			g.DoExit();
	}

	g.FinalCleanup();
}


#pragma once

namespace app
{
	enum class Screens
	{
		Menu = 0, Gameplay, GameOver, Credits, Gameplay2
	};

	extern bool exit;
	extern Screens currentScreen;
	

	void ExecuteGame();
}


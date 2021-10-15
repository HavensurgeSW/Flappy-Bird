#pragma once
#include "raylib.h"

namespace app
{
	namespace game
	{
		void InitValues();
		void UpdateFrame();
		void Draw();
		void RandomizeGap();
		void ResetValues();
		void UnloadGameplay();

		extern bool victory;
		extern bool gameOver;
	}
}

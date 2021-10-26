#pragma once
#include "raylib.h"

namespace app
{
	namespace game
	{
		void InitValues();
		void UpdateFrame();
		void UpdateFrame2();
		void Draw();
		void Draw2();
		void ResetValues();
		void UnloadGameplay();

		extern bool victory;
		extern bool gameOver;
	}
}

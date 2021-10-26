#include "app.h"
#include "raylib.h"

#include "game.h"
#include "menu.h"
#include "credits.h"

#include <iostream>
#include <time.h>

using namespace app;
using namespace game;
using namespace menu;
using namespace credits;

namespace app
{
	static int screenWidth = 1280;
	static int screenHeight = 768;
	bool exit = false;
	Screens currentScreen = Menu;

	static void InitGame()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "Flappy Bird");
		SetTargetFPS(60);


		InitValues();
		InitMenu();
		InitCredits();

	}

	static void UpdateGame()
	{
		switch (currentScreen)
		{
		case Menu:
			UpdateMenu();
			break;
		case Credits:
			UpdateCredits();
			break;
		case Gameplay:
			UpdateFrame();
			break;
		case GameOver:
			break;
		case Gameplay2:
			UpdateFrame2();
			break;
		default:
			break;
		}
	}

	static void DrawGame()
	{
		BeginDrawing();
		switch (currentScreen)
		{
		case Menu:
			DrawMenu();
			break;
		case Credits:
			DrawCredits();
			break;
		case Gameplay:
			Draw();
			break;
		case GameOver:
			break;
		case Gameplay2:
			Draw2();
			break;
		default:
			break;
		}
		EndDrawing();
	}

	static void CloseGame()
	{
		CloseWindow();
	}

	void ExecuteGame()
	{
		srand(time(NULL));

		InitGame();
		// Main game loop
		while (!WindowShouldClose() && !exit)
		{
			UpdateGame();
			DrawGame();
		}
		CloseGame();
	}
}
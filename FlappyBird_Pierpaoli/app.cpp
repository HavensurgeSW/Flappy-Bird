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
	Screens currentScreen = Screens::Menu;
	static Music gameMusic;
	

	static void InitGame()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "Flappy Bird");
		SetTargetFPS(60);


		InitValues();
		InitMenu();
		InitCredits();

		InitAudioDevice();
		gameMusic = LoadMusicStream("res/ambience.mp3");
		PlayMusicStream(gameMusic);
		SetMusicVolume(gameMusic, 0.2f);

	}

	static void UpdateGame()
	{
		UpdateMusicStream(gameMusic);
		switch (currentScreen)
		{
		case Screens::Menu:
			UpdateMenu();
			break;
		case Screens::Credits:
			UpdateCredits();
			break;
		case Screens::Gameplay:
			UpdateFrame();
			break;
		case Screens::GameOver:
			break;
		case Screens::Gameplay2:
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
		case Screens::Menu:
			DrawMenu();
			break;
		case Screens::Credits:
			DrawCredits();
			break;
		case Screens::Gameplay:
			Draw();
			break;
		case Screens::GameOver:
			break;
		case Screens::Gameplay2:
			Draw2();
			break;
		default:
			break;
		}
		EndDrawing();
	}

	static void CloseGame()
	{
		CloseAudioDevice();
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
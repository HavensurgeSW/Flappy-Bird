#include "app.h"
#include "raylib.h"

#include "game.h"

using namespace app;
using namespace game;

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
		InitValues();						
	}

	static void UpdateGame()
	{		
		switch (currentScreen)
		{
		case Menu:			
			break;
		case Credits:			
			break;
		case Gameplay:
			UpdateFrame();
			break;
		case GameOver:			
			break;
		case Pause:			
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
			break;
		case Credits:			
			break;
		case Gameplay:			
			break;
		case GameOver:			
			break;
		case Pause:			
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
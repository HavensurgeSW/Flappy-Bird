#include "credits.h"

#include <raylib.h>

#include "game.h"
#include "app.h"
#include "menu.h"

using namespace app;
using namespace game;
using namespace menu;

namespace app
{
	namespace credits
	{
		static char text1[] = "Created by Pierpaoli Matias";
		static char text2[] = "MENU";
		static char text3[] = "V 0.3";
		static char text4[] = "Art by Karplus Matias";

		static int sizeText = 0;
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int textPositionX = 0;
		static int textPositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;


		static int halfScreen = 0;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;

		static Vector2 mousePoint;
		static Rectangle rect1;
		static Color colorRect1;

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 20) / scaleAux1;
			sizeText2 = (GetScreenWidth() * 15) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 12.f) / scaleAux1;
			halfScreen = GetScreenWidth() / 2;

			// Created by Pierpaoli Matias
			textPositionX = halfScreen - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.45;

			text4PositionX = halfScreen - MeasureText(text4, sizeText) / 2;
			text4PositionY = GetScreenHeight() * 0.55;

			// MENU
			text2PositionX = halfScreen - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.80;

			// V 0.1
			text3PositionX = GetScreenWidth() * 0.05;
			text3PositionY = GetScreenHeight() * 0.95;

			colorRect1 = RED;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 170) / scaleAux2;
			rect1.x = halfScreen - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;
		}

		void UpdateCredits()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					InitMenu();
				}
			}
			else colorRect1.a = 255;
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawText(text1, textPositionX, textPositionY, sizeText, RED);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, RED);
			DrawText(text4, text4PositionX, text4PositionY, sizeText, RED);
		
		}
	}
}
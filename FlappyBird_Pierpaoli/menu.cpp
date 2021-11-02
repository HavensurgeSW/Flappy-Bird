#include "menu.h"

#include "raylib.h"

#include "app.h"
#include "game.h"

using namespace app;
using namespace game;

namespace app
{
	namespace menu
	{
		static char text1[] = "JUGAR";
		static char text2[] = "CREDITOS";
		static char text3[] = "SALIR";
		static char text4[] = "V 1.0";

		static char text5[] = "1 Jugador";
		static char text6[] = "2 Jugadores";
		static char text7[] = "Flap & Cloak";

		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int text1PositionX = 0;
		static int text1PositionY = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;

		static int text5PositionY = 0;
		static int text5PositionX = 0;

		static int text6PositionY = 0;
		static int text6PositionX = 0;
		static int text7PositionY = 0;
		static int text7PositionX = 0;


		static Vector2 mousePoint;
		static Rectangle rect1;
		static Rectangle rect2;
		static Rectangle rect3;

		static Rectangle rect4;
		static Rectangle rect5;


		static Color colorRect1;
		static Color colorRect2;
		static Color colorRect3;
		static Color colorRect4;
		static Color colorRect5;



		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;
		static const int scaleAux3 = 1280;

		static int halfScreenWidth = 0;
		static int halfScreenHeight = 0;

		static float scaleBackground;
		static bool ready = false;

		static Music gameMusic = LoadMusicStream("res/ambience.mp3");

		void InitMenu()
		{
			PlayMusicStream(gameMusic);

			halfScreenWidth = GetScreenWidth() / 2;
			halfScreenHeight = GetScreenHeight() / 2;

			sizeText2 = (GetScreenWidth() * 20) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 15) / scaleAux1;

			// Jugar
			text1PositionX = halfScreenWidth - MeasureText(text1, sizeText2) / 2;
			text1PositionY = halfScreenHeight + GetScreenHeight() * 0.0333333;

			// Creditos
			text2PositionX = halfScreenWidth - MeasureText(text2, sizeText2) / 2;
			text2PositionY = halfScreenHeight + GetScreenHeight() * 0.2333333;

			// Salir
			text3PositionX = halfScreenWidth - MeasureText(text3, sizeText2) / 2;
			text3PositionY = halfScreenHeight + GetScreenHeight() * 0.3333333;

			text5PositionX = halfScreenWidth - MeasureText(text5, sizeText2) / 2;
			text5PositionY = halfScreenHeight + GetScreenHeight() * 0.1333333;

			text6PositionX = halfScreenWidth + MeasureText(text6, sizeText2) / 1.5f+5;
			text6PositionY = halfScreenHeight + GetScreenHeight() * 0.1333333;

			text7PositionX = halfScreenWidth - MeasureText(text7, sizeText2) / 2;
			text7PositionY = halfScreenHeight - GetScreenHeight() * 0.2333333;

			// Version
			text4PositionX = GetScreenWidth() * 0.05;
			text4PositionY = GetScreenHeight() * 0.95;

			colorRect1 = RED;
			colorRect2 = RED;
			colorRect3 = RED;
			colorRect4 = RED;
			colorRect5 = RED;

			// Recatngulo 2
			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 255) / scaleAux2;
			rect1.x = halfScreenWidth - rect1.width / 2;
			rect1.y = halfScreenHeight + GetScreenHeight() * 0.21;

			// Recatngulo 3
			rect2.height = (GetScreenWidth() * 80) / scaleAux2;
			rect2.width = (GetScreenWidth() * 255) / scaleAux2;
			rect2.x = halfScreenWidth - rect1.width / 2;
			rect2.y = halfScreenHeight + GetScreenHeight() * 0.31;


			// Rectangulo 1 (JUGAR)
			rect3.height = (GetScreenWidth() * 80) / scaleAux2;
			rect3.width = (GetScreenWidth() * 255) / scaleAux2;
			rect3.x = halfScreenWidth - rect1.width / 2;
			rect3.y = halfScreenHeight + GetScreenHeight() * 0.01;

			// Rectangulo 4 (1 JUGADOR)
			rect4.height = (GetScreenWidth() * 80) / scaleAux2;
			rect4.width = (GetScreenWidth() * 255) / scaleAux2;
			rect4.x = halfScreenWidth - rect4.width / 2;
			rect4.y = halfScreenHeight + GetScreenHeight() * 0.11;

			// Rectangulo 5 (2 JUGADORES)
			rect5.height = (GetScreenWidth() * 80) / scaleAux2;
			rect5.width = (GetScreenWidth() * 255) / scaleAux2;
			rect5.x = halfScreenWidth + rect4.width / 1.5f;
			rect5.y = halfScreenHeight + GetScreenHeight() * 0.11;

			scaleBackground = (GetScreenWidth() * 1.0f) / scaleAux3;
		}

		void UpdateMenu()
		{
			UpdateMusicStream(gameMusic);
			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					UnloadMenu();
					currentScreen = Screens::Credits;
					ready = false;
				}
			}
			else colorRect1.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect2))
			{
				colorRect2.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					exit = true;
				}
			}
			else colorRect2.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect3))
			{
				colorRect3.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					ready = true;
					
				}
			}
			else colorRect3.a = 255;

			if (ready)
			{
				if (CheckCollisionPointRec(mousePoint, rect4))
				{
					colorRect4.a = 120;

					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						UnloadMenu();
						InitValues();
						currentScreen = Screens::Gameplay;
						ready = false;
					}
				}
				else colorRect4.a = 255;

				if (CheckCollisionPointRec(mousePoint, rect5))
				{
					colorRect5.a = 120;

					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						UnloadMenu();
						InitValues();
						currentScreen = Screens::Gameplay2;
						ready = false;
					}
				}
				else colorRect5.a = 255;
			}
		}

		void DrawMenu()
		{
			ClearBackground(BLACK);

			if (!ready)
			{
				DrawRectangleRec(rect3, colorRect3);
				DrawText(text1, text1PositionX, text1PositionY, sizeText2, BLACK);
			}

			DrawRectangleRec(rect1, colorRect1);
			DrawRectangleRec(rect2, colorRect2);


			DrawText(text2, text2PositionX, text2PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, RED);
			DrawText(text7, text7PositionX-140, text7PositionY, 80, RED);

			if (ready)
			{
				DrawRectangleRec(rect4, colorRect4);
				DrawRectangleRec(rect5, colorRect5);
				DrawText(text5, text5PositionX, text5PositionY, sizeText2, BLACK);
				DrawText(text6, text6PositionX, text6PositionY, sizeText2, BLACK);
			}

		}

		void UnloadMenu()
		{

		}
	}
}
#include "game.h"

#include "app.h"

using namespace app;


namespace app
{
	namespace game
	{
		extern bool victory = false;
		extern bool gameOver = false;
		bool pause = false;
		static char text[] = "";
		static int sizeText;
		static float textPositionX;
		static float textPositionY;		

		//Boton pausa
		static Rectangle btnPause1;
		static Rectangle btnPause2;
		static Color colorRect;
		static Vector2 mousePoint;

		static bool init;

		struct Flappy
		{
			Vector2 position;
			int radius;
			Color color;
		};

		Flappy flappy;

		void InitValues()
		{
			sizeText = (GetScreenWidth() * 20) / 1600;
			textPositionX = GetScreenWidth() * 0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			//init boton pausa
			btnPause1.x = GetScreenWidth() * 0.96f;
			btnPause1.y = GetScreenHeight() * 0.02f;
			btnPause1.height = (GetScreenWidth() * 40) / 1600;
			btnPause1.width = (GetScreenWidth() * 15) / 1600;
			btnPause2.x = GetScreenWidth() * 0.975f;
			btnPause2.y = GetScreenHeight() * 0.02f;
			btnPause2.height = (GetScreenWidth() * 40) / 1600;
			btnPause2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;		


			flappy.radius = 24;
			//flappy.position = Vector2{ 80, GetScreenHeight() / 2 - flappy.radius };
			flappy.position.x = 80;
			flappy.position.y = GetScreenHeight() / 2 - flappy.radius;

			
		}


		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, btnPause1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, btnPause2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}

		}

		static void Update()
		{
			if (!gameOver)
			{
				if (IsKeyPressed('P')) pause = !pause;

				if (!pause)
				{




					if (IsKeyDown(KEY_UP) && !gameOver) flappy.position.y -= 3;
					else if (IsKeyDown(KEY_DOWN) && !gameOver) flappy.position.y += 3;
					
				}
			}
		}

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);			

			DrawRectangleRec(btnPause1, colorRect);
			DrawRectangleRec(btnPause2, colorRect);
			DrawText(text, textPositionX, textPositionY, sizeText, RED);

			if (!gameOver)
			{
				DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, RED);



				if (pause)
				{
					DrawText("Pausado", GetScreenWidth()/2 - MeasureText("Pausado", 40)/2, GetScreenHeight()/2 - 40, 40, RED);
				}
			}
		}

		void ResetValues()
		{
			InitValues();
			gameOver = false;
			pause = false;
		}

		void UnloadGameplay()
		{
			
		}
	}
}
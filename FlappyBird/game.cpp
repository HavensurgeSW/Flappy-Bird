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

		int tubeSpeedX = 0;

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

		struct Tubes
		{
			Rectangle rec;
			bool active;
			Color color;
		};

		Flappy flappy;

		Tubes tube;
		Vector2 tubePos;

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

			tubeSpeedX = 2;

			flappy.radius = 24;
			flappy.position.x = 80;
			flappy.position.y = GetScreenHeight() / 2 - flappy.radius;

			tubePos.x = 400 + 280;
			tubePos.y = -GetRandomValue(0, 120);

			tube.rec.x = tubePos.x;
			tube.rec.y = tubePos.y;
			tube.rec.width = 80;
			tube.rec.height = 255;

			tube.active = true;
			
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
					tubePos.x -= tubeSpeedX;

					tube.rec.x = tubePos.x;
			
					if (CheckCollisionCircleRec(flappy.position, flappy.radius, tube.rec))
					{
						gameOver = true;
						pause = false;
					}
					else if ((tubePos.x < flappy.position) && tube.active && !gameOver)
					{
						tube.active = false;
					}



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

				DrawRectangle(tube.rec.x, tube.rec.y, tube.rec.width, tube.rec.height, BLUE);

				if (pause)
				{
					DrawText("Pausado", GetScreenWidth()/2 - MeasureText("Pausado", 40)/2, GetScreenHeight()/2 - 40, 40, RED);
				}
			}
			else
			{
				if (IsKeyPressed(KEY_ENTER))
				{				
					ResetValues();
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
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

		const int maxTubes = 1;

		Tubes tubes[maxTubes];
		Vector2 tubesPos[maxTubes];

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

			tubeSpeedX = 300 * GetFrameTime();

			flappy.radius = 24;
			flappy.position.x = 80;
			flappy.position.y = GetScreenHeight() / 2 - flappy.radius;

			for (int i = 0; i < maxTubes; i++)
			{
				tubesPos[i].x = GetScreenWidth();
				tubesPos[i].y = -GetRandomValue(0, 120);
			}
			
			for (int i = 0; i < maxTubes*2; i++)
			{
				tubes[i].rec.x = tubesPos[i/2].x;
				tubes[i].rec.y = tubesPos[i/2].y;
				tubes[i].rec.width = 80;
				tubes[i].rec.height = GetScreenHeight() / 2 - 50;

				
				tubes[i + 1].rec.width = 80;
				tubes[i + 1].rec.height = GetScreenHeight() / 2 - 50;
				tubes[i + 1].rec.x = tubesPos[i / 2].x;
				tubes[i + 1].rec.y = GetScreenHeight() - tubes[i + 1].rec.height; 

				tubes[i].active = true;
			}

			gameOver = false;
			pause = false;
			
		}


		static void Input()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, btnPause1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pause = !pause;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, btnPause2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pause = !pause;
			}

			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				if (IsKeyDown(KEY_UP) && !gameOver)
				{
					flappy.position.y -= 3;
				}
				else if (IsKeyDown(KEY_DOWN) && !gameOver)
				{
					flappy.position.y += 3;
				}
			}

			

		}

		static void Update()
		{
			if (!gameOver)
			{				
				if (!pause)
				{
					for (int i = 0; i < maxTubes; i++)
					{
						tubesPos[i].x -= tubeSpeedX;
					}

					for (int i = 0; i < maxTubes*2; i += 2)
					{
						tubes[i].rec.x = tubesPos[i/2].x;
						tubes[i + 1].rec.x = tubesPos[i / 2].x;
					}
								
					for (int i = 0; i < maxTubes*2; i++)
					{
						if (tubes[i].rec.x <= 0 && tubes[i].active && !gameOver)
						{
							/*tubesPos[i].x = GetScreenWidth();
							tubesPos[i].y = -GetRandomValue(0, 120);*/

							/*tubes[i + 1].rec.x = tubesPos[i / 2].x;
							tubes[i + 1].rec.y = tubesPos[i / 2].y;*/

							tubes[i].rec.x = GetScreenWidth();
							//tubesPos[i].x = GetScreenWidth();

							tubes[i + 1].rec.x = GetScreenWidth();
							//tubes[i + 1].rec.y = GetScreenHeight();

						}

					}
					for (int i = 0; i < maxTubes * 2; i++)
					{
						if (CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i].rec))
						{
							gameOver = true;
							pause = false;
						}
					}
					

					

					
					/*else if ((tubePos.x < flappy.position.x) && tube.active && !gameOver)
					{
						tube.active = false;
					}	*/			
				}
			}
		}

		void UpdateFrame()
		{			
			Update();
			Input();
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

				for (int i = 0; i < maxTubes; i++)
				{
					DrawRectangle(tubes[i].rec.x, tubes[i].rec.y, tubes[i].rec.width, tubes[i].rec.height, BLUE);
					DrawRectangle(tubes[i*2+1].rec.x, tubes[i * 2 + 1].rec.y, tubes[i * 2 + 1].rec.width, tubes[i * 2 + 1].rec.height, BLUE);
				}

				

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
						
		}

		void UnloadGameplay()
		{
			
		}
	}
}
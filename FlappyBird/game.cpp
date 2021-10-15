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

		enum GapCases {
			Case1 = 1, Case2, Case3
		};

		Flappy flappy;

		const int maxTubes = 2;

		Tubes tubes[maxTubes];
		Vector2 tubesPos[maxTubes];

		GapCases gapCases;

		static int gap = 0;

		static int rnd = 0;

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

			gap = 200;
						
			RandomizeGap();
			
			tubes[0].active = true;
			tubes[1].active = true;
			
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
					
					tubes[0].rec.x = tubesPos[0].x;
					tubes[1].rec.x = tubesPos[0].x;
																		
					if (tubes[0].rec.x <= 0 && tubes[0].active && !gameOver)
					{						
						RandomizeGap();
					}
					
					for (int i = 0; i < maxTubes; i++)
					{
						if (CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i].rec))
						{
							gameOver = true;
							pause = false;
						}
					}						
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

				
				DrawRectangle(tubes[0].rec.x, tubes[0].rec.y, tubes[0].rec.width, tubes[0].rec.height, BLUE);
				DrawRectangle(tubes[1].rec.x, tubes[1].rec.y, tubes[1].rec.width, tubes[1].rec.height, BLUE);
				

				

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

		void RandomizeGap()
		{
			rnd = GetRandomValue(1, 3);

			switch (rnd)
			{
			case 1:
				gapCases = GapCases::Case1;
				break;
			case 2:
				gapCases = GapCases::Case2;
				break;
			case 3:
				gapCases = GapCases::Case3;
				break;
			default:
				break;
			}

			switch (gapCases)
			{
			case app::game::Case1:
				for (int i = 0; i < maxTubes; i++)
				{
					tubesPos[i].x = GetScreenWidth();
				}

				tubes[0].rec.x = tubesPos[0].x;
				tubes[0].rec.y = 0;
				tubes[0].rec.width = 80;
				tubes[0].rec.height = GetScreenHeight() / 2 - gap / 2;

				tubes[1].rec.x = tubesPos[0].x;
				tubes[1].rec.y = tubes[0].rec.height + gap / 2;
				tubes[1].rec.width = 80;
				tubes[1].rec.height = GetScreenHeight() - tubes[1].rec.y;

				break;
			case app::game::Case2:
				for (int i = 0; i < maxTubes; i++)
				{
					tubesPos[i].x = GetScreenWidth();
				}

				tubes[0].rec.x = tubesPos[0].x;
				tubes[0].rec.y = 0;
				tubes[0].rec.width = 80;
				tubes[0].rec.height = GetScreenHeight() / 3 - gap / 2;

				tubes[1].rec.x = tubesPos[0].x;
				tubes[1].rec.y = tubes[0].rec.height + gap / 2;
				tubes[1].rec.width = 80;
				tubes[1].rec.height = GetScreenHeight() - tubes[1].rec.y;
				break;
			case app::game::Case3:
				for (int i = 0; i < maxTubes; i++)
				{
					tubesPos[i].x = GetScreenWidth();
				}

				tubes[0].rec.x = tubesPos[0].x;
				tubes[0].rec.y = 0;
				tubes[0].rec.width = 80;
				tubes[0].rec.height = GetScreenHeight() - 100 - gap / 2;

				tubes[1].rec.x = tubesPos[0].x;
				tubes[1].rec.y = tubes[0].rec.height + gap / 2;
				tubes[1].rec.width = 80;
				tubes[1].rec.height = GetScreenHeight() - tubes[1].rec.y;
				break;
			default:
				break;
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
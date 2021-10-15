#include "game.h"

#include "app.h"
#include "menu.h"

using namespace app;
using namespace menu;



namespace app
{
	namespace game
	{
		

		extern bool victory = false;
		extern bool gameOver = false;
		bool pause = false;
		static char text[] = "Pausado";
		static char text2[] = "You loose";
		static char text3[] = "Menu";
		static char text4[] = "Press Enter to restart";
		
		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;

		static int sizeText;
		static int sizeText2;
		static int sizeText3;
		static float textPositionX;
		static float textPositionY;		
		static float text2PositionX;
		static float text2PositionY;
		static float text3PositionX;
		static float text3PositionY;
		static float text4PositionX;
		static float text4PositionY;

		static Rectangle rect1;
		static Color colorRect1;

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
			// Pausado
			textPositionX = GetScreenWidth() / 2 - MeasureText(text, 40) / 2;
			textPositionY = GetScreenHeight() / 2 - 40;

			// You loose
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, 40) / 2;
			text2PositionY = GetScreenHeight() * 0.50f;

			// Menu
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, 40) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.289;			

			// Press Enter to return to Menu
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, 40) / 2;
			text4PositionY = GetScreenHeight() * 0.90f;

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


			// Rectangulo para Menu
			colorRect1 = RED;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 170) / scaleAux2;
			rect1.x = GetScreenWidth()/2 - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;

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

			if (!gameOver)
			{
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
			

			if (!gameOver)
			{
				DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, RED);

				
				DrawRectangle(tubes[0].rec.x, tubes[0].rec.y, tubes[0].rec.width, tubes[0].rec.height, BLUE);
				DrawRectangle(tubes[1].rec.x, tubes[1].rec.y, tubes[1].rec.width, tubes[1].rec.height, BLUE);

				if (pause)
				{
					DrawText(text, textPositionX, textPositionY, 40, RED);
				}
			}
			else
			{
				DrawRectangleRec(rect1, colorRect1);
				DrawText(text2, text2PositionX, text2PositionY, 40, RED);			
				DrawText(text3, text3PositionX, text3PositionY, 40, BLACK);
				DrawText(text4, text4PositionX, text4PositionY, 40, RED);
				
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

				if (IsKeyPressed(KEY_ENTER)) ResetValues();				
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
#include "game.h"

#include "app.h"
#include "menu.h"

using namespace app;
using namespace menu;



namespace app
{
	namespace game
	{

		static Image birdImage;
		static Texture2D birdTex1;
		static Texture2D birdTex2;
		static Texture2D birdTexture;
	
		static Rectangle sourceRect;
		static Rectangle destRec;

		static float birdScale;
		static float birdRotation;

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
		Flappy flappy2;

		const int maxTubes = 100000;

		Tubes tubes[maxTubes * 2];
		Vector2 tubesPos[maxTubes];

		GapCases gapCases;

		static int gap = 0;

		static int rnd = 0;

		static float acceleration;
		static float gravity;
		static float flappingForce;

		void InitValues()
		{
			birdTex1 = LoadTexture("res/CGf1.png");
			birdTex2 = LoadTexture("res/CGf2.png");
			birdTexture = LoadTextureFromImage(birdImage);

			sourceRect.height = birdTexture.height;
			sourceRect.width = birdTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			birdScale = (GetScreenWidth() * 0.08f) / scaleAux2;
			birdRotation = 0;


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
			rect1.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;

			tubeSpeedX = 250 * GetFrameTime();

			flappy.radius = 20;
			flappy.position.x = 80;
			flappy.position.y = GetScreenHeight() / 2 - flappy.radius;

			flappy2.radius = 20;
			flappy2.position.x = 80;
			flappy2.position.y = GetScreenHeight() / 2 - flappy.radius;

			gap = 150;

			acceleration = 0.0f;

			gravity = 13000.0f;
			flappingForce = 17000.0f;

			for (int i = 0; i < maxTubes; i++)
			{
				tubesPos[i].x = 800 + 600 * i;
			}

			for (int i = 0; i < maxTubes * 2; i += 2)
			{
				tubes[i].rec.x = tubesPos[i / 2].x;
				tubes[i].rec.y = 0;
				tubes[i].rec.width = 80;
				tubes[i].rec.height = GetRandomValue(0, GetScreenHeight() - 200);

				tubes[i + 1].rec.x = tubesPos[i / 2].x;
				tubes[i + 1].rec.y = tubes[i].rec.height + gap;
				tubes[i + 1].rec.width = 80;
				tubes[i + 1].rec.height = GetScreenHeight() - tubes[i].rec.height;


				tubes[i / 2].active = true;
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

			if (!gameOver)
			{
				if (!pause)
				{
					if (IsKeyDown(KEY_SPACE))
					{
						flappy.position.y -= GetFrameTime()*300;

					}
					else
					{
						flappy.position.y += GetFrameTime() * 170;
					}

				}
			}

		}
		static void Input2()
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
					if (IsKeyDown(KEY_SPACE))
					{
						flappy.position.y -= GetFrameTime() * 300;

					}
					else
					{
						flappy.position.y += GetFrameTime() * 170;
					}

					if (IsKeyDown(KEY_ENTER))
					{
						flappy2.position.y -= GetFrameTime() * 300;

					}
					else
					{
						flappy2.position.y += GetFrameTime() * 170;
					}

				}
			}

		}


		static void Update()
		{
			if (!gameOver)
			{
				destRec.x = flappy.position.x;
				destRec.y = flappy.position.y;

				if (!pause)
				{
					for (int i = 0; i < maxTubes; i++)
					{
						tubesPos[i].x -= tubeSpeedX;
					}

					for (int i = 0; i < maxTubes * 2; i += 2)
					{
						tubes[i].rec.x = tubesPos[i / 2].x;
						tubes[i + 1].rec.x = tubesPos[i / 2].x;
					}

					if (flappy.position.y <= 0)
					{
						flappy.position.y = 0;
					}
					else if (flappy.position.y >= GetScreenHeight())
					{
						flappy.position.y = GetScreenHeight();
					}


					for (int i = 0; i < maxTubes * 2; i++)
					{
						if (CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i].rec))
						{
							gameOver = true;
							pause = false;
						}
						if ((tubesPos[i / 2].x <= 0) && tubes[i / 2].active && !gameOver)
						{
							tubes[i / 2].active = false;
						}
					}
				}
			}
		}
		static void Update2()
		{
			if (!gameOver)
			{
				destRec.x = flappy.position.x;
				destRec.y = flappy.position.y;

				if (!pause)
				{
					for (int i = 0; i < maxTubes; i++)
					{
						tubesPos[i].x -= tubeSpeedX;
					}

					for (int i = 0; i < maxTubes * 2; i += 2)
					{
						tubes[i].rec.x = tubesPos[i / 2].x;
						tubes[i + 1].rec.x = tubesPos[i / 2].x;
					}

					if (flappy.position.y <= 0)
					{
						flappy.position.y = 0;
					}
					else if (flappy.position.y >= GetScreenHeight())
					{
						flappy.position.y = GetScreenHeight();
					}

					if (flappy2.position.y <= 0)
					{
						flappy2.position.y = 0;
					}
					else if (flappy2.position.y >= GetScreenHeight())
					{
						flappy2.position.y = GetScreenHeight();
					}



					for (int i = 0; i < maxTubes * 2; i++)
					{
						if (CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i].rec))
						{
							gameOver = true;
							pause = false;
						}
						if ((tubesPos[i / 2].x <= 0) && tubes[i / 2].active && !gameOver)
						{
							tubes[i / 2].active = false;
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
		void UpdateFrame2()
		{
			Update2();
			Input2();
		}
		


		void Draw()
		{
			ClearBackground(BLANK);

			DrawRectangleRec(btnPause1, colorRect);
			DrawRectangleRec(btnPause2, colorRect);


			if (!gameOver)
			{
				DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, RED);
				DrawTexture(birdTex1, flappy.position.x - flappy.radius, flappy.position.y - flappy.radius, WHITE);
				
				for (int i = 0; i < maxTubes; i++)
				{
					DrawRectangle(tubes[i * 2].rec.x, tubes[i * 2].rec.y, tubes[i * 2].rec.width, tubes[i * 2].rec.height, BLUE);
					DrawRectangle(tubes[i * 2 + 1].rec.x, tubes[i * 2 + 1].rec.y, tubes[i * 2 + 1].rec.width, tubes[i * 2 + 1].rec.height, BLUE);
				}

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
		void Draw2()
		{
			ClearBackground(BLANK);

			DrawRectangleRec(btnPause1, colorRect);
			DrawRectangleRec(btnPause2, colorRect);


			if (!gameOver)
			{
				DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, RED);
				DrawCircle(flappy2.position.x, flappy2.position.y, flappy2.radius, SKYBLUE);

				DrawTexture(birdTex1, flappy.position.x-flappy.radius, flappy.position.y-flappy.radius, WHITE);
				DrawTexture(birdTex1, flappy2.position.x - flappy2.radius, flappy2.position.y - flappy2.radius, RED);



				for (int i = 0; i < maxTubes; i++)
				{
					DrawRectangle(tubes[i * 2].rec.x, tubes[i * 2].rec.y, tubes[i * 2].rec.width, tubes[i * 2].rec.height, BLUE);
					DrawRectangle(tubes[i * 2 + 1].rec.x, tubes[i * 2 + 1].rec.y, tubes[i * 2 + 1].rec.width, tubes[i * 2 + 1].rec.height, BLUE);
				}

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

		void ResetValues()
		{
			InitValues();
		}

		void UnloadGameplay()
		{
			UnloadImage(birdImage);
			UnloadTexture(birdTexture);
		}
	}
}
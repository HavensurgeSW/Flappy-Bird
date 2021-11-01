#include "parallax.h"


Parallax::Parallax()
{
	converter = GetScreenWidth();
	layer1 = LoadTexture("test");
	layer2 = LoadTexture("test");
	layer3 = LoadTexture("test");
	layer4 = LoadTexture("test");
	l1 = { 0,0 };
	l2 = { 0,0 };
	l3 = { 0,0 };
	l4 = { 0,0 };

	l1d = { converter,0 };
	l2d = { converter,0 };
	l3d = { converter,0 };
	l4d = { converter,0 };
}

Parallax::~Parallax()
{
	UnloadTexture(layer1);
	UnloadTexture(layer2);
	UnloadTexture(layer3);
	UnloadTexture(layer4);
}

void Parallax::draw()
{
	DrawTextureEx(layer4, l4, 0, 2.1f, WHITE);
	DrawTextureEx(layer4, l4d, 0, 2.1f, WHITE);

	DrawTextureEx(layer3, l3, 0, 2.1f, WHITE);
	DrawTextureEx(layer3, l3d, 0, 2.1f, WHITE);

	DrawTextureEx(layer2, l2, 0, 2.1f, WHITE);
	DrawTextureEx(layer2, l2d, 0, 2.1f, WHITE);

	DrawTextureEx(layer1, l1, 0, 2.1f, WHITE);
	DrawTextureEx(layer1, l1d, 0, 2.1f, WHITE);
}

void Parallax::update()
{
	l1.x -= GetFrameTime() * 100;
	l2.x -= GetFrameTime() * 50;
	l3.x -= GetFrameTime() * 10;
	l4.x -= GetFrameTime() * 5;

	l1d.x -= GetFrameTime() * 100;
	l2d.x -= GetFrameTime() * 50;
	l3d.x -= GetFrameTime() * 10;
	l4d.x -= GetFrameTime() * 5;

	if (l1.x < -800)
	{
		l1.x = converter;
	}
	if (l2.x < -800)
	{
		l2.x = converter;
	}
	if (l3.x < -800)
	{
		l3.x = converter;
	}
	if (l4.x < -800)
	{
		l4.x = converter;
	}
	if (l1d.x < -800)
	{
		l1d.x = converter;
	}
	if (l2d.x < -800)
	{
		l2d.x = converter;
	}
	if (l3d.x < -800)
	{
		l3d.x = converter;
	}
	if (l4d.x < -800)
	{
		l4d.x = converter;
	}
}


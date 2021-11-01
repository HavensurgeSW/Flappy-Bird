#pragma once
#include "raylib.h"



		class Parallax {
		private:
			//Layer 1 is FRONT (Close to player, moves fastest)
			//Load AFTER WindowInit (OpenGL context needed)
			float converter;
			Texture2D layer1;
			Texture2D layer2;
			Texture2D layer3;
			Texture2D layer4;
			Vector2 l1;
			Vector2 l2;
			Vector2 l3;
			Vector2 l4;

			Vector2 l1d;
			Vector2 l2d;
			Vector2 l3d;
			Vector2 l4d;
		public:
			Parallax();
			~Parallax();
			void draw();
			void update();
		};

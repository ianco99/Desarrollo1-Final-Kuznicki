#pragma once
#include "raylib.h"

struct BackgroundImage
{
	Color color;
	Texture2D sprite;
	int speedX;
	Rectangle body;
	int layer;
};
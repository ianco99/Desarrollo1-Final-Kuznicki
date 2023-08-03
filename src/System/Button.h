#pragma once
#include "raylib.h"

namespace kuznickiSystem
{
	const int textLimit = 256;
	const float buttonXDivider = 4.0f;
	const float buttonYDivider = 12.0f;
	struct Button
	{
		Rectangle body;
		Font font;
		Color color;
		Texture2D* sprite;
		const char* text;
		const char* link;
		float fontSize;
		float fontSpacing;
	};
}
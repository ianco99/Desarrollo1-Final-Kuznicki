#pragma once
#include "raylib.h"

namespace kuznickiSystem
{
	const int textLimit = 256;
	struct Button
	{
		Font font;
		Rectangle body;
		Color color;
		char text[textLimit];
		float fontSize;
		float fontSpacing;
	};
}
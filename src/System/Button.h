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
		const char* text;
		const char* link;
		float fontSize;
		float fontSpacing;
	};
}
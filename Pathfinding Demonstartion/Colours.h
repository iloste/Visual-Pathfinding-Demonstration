#pragma once
#include "SDL.h"

class Colours
{
public:
	enum class Colour
	{
		Black,
		Red,
		Green,
		White,
		Brown,
		NavyBlue,
		RiverBlue,
		Blue,

	};

	static int* getColour(Colour colour);
	static inline void tintColour(SDL_Colour& colour, float factor)
	{
		colour.r = colour.r + (255 - colour.r) * factor;
		colour.g = colour.g + (255 - colour.g) * factor;
		colour.b = colour.b + (255 - colour.b) * factor;
	}
	static inline void shadeColour(SDL_Colour& colour, float factor)
	{
		colour.r = colour.r * (1 - factor);
		colour.g = colour.g * (1 - factor);
		colour.b = colour.b * (1 - factor);
	}

	//const static  int _black[4]{ 0, 0, 0, 255 };

};


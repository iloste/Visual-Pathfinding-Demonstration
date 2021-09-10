#include "Colours.h"


int* Colours::getColour(Colour colour)
{
	static int c[4]{ 0, 0, 0, 255 };
	switch (colour)
	{
	case Colours::Colour::Black:
		c[0] = 0;
		c[1] = 0;
		c[2] = 0;
		break;
	case Colours::Colour::Red:
		c[0] = 255;
		c[1] = 0;
		c[2] = 0;
		break;
	case Colours::Colour::Green:
		c[0] = 0;
		c[1] = 255;
		c[2] = 0;
		break;
	case Colours::Colour::White:
		c[0] = 235;
		c[1] = 235;
		c[2] = 235;
		break;
	case Colours::Colour::Brown:
		c[0] = 139;
		c[1] = 69;
		c[2] = 19;
		break;
	case Colours::Colour::NavyBlue:
		c[0] = 0;
		c[1] = 0;
		c[2] = 128;
		break;
	case Colours::Colour::Blue:
		c[0] = 0;
		c[1] = 0;
		c[2] = 255;
		break;
	case Colours::Colour::RiverBlue:
		c[0] = 101;
		c[1] = 187;
		c[2] = 199;
		break;
	}
	return c;
}


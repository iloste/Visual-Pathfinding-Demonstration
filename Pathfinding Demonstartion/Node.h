#pragma once
#include <SDL.h>
//#include "PathfindingNodeObsolete.h"
#include "PathfindingNode.h"


struct Node:PathfindingLibrary::PathfindingNode
{
	// this should be a pointer############################################
	SDL_Rect _rect{};
	SDL_Colour _colour{};
};


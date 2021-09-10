#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <memory>
#include <iostream>

class Text
{
public:
	Text();
	Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, const std::string& message, const SDL_Color& colour);
	void displayText(SDL_Renderer* renderer,int x, int y) const;

	static SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, const std::string& message, const SDL_Color& colour);
	std::string _message{};

private:
	SDL_Texture* _texture{ nullptr };
	mutable SDL_Rect* _rect{};
};


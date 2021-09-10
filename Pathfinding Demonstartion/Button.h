#pragma once
#include "Colours.h"
#include "Text.h"
#include <SDL.h>
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include <functional>


enum class ButtonStates
{
	Normal,
	Hovered,
	Clicked,
};

class Button
{
public:
	Button();
	Button(SDL_Renderer* renderer, int pos[2], int width, int height, std::string buttonText, int fontSize,
		std::function<void()> function);
	~Button();

	void setButtonState(ButtonStates state);
	void displayButton(SDL_Renderer* renderer);
	void onClick();

	ButtonStates _buttonState{ ButtonStates::Normal };
	SDL_Rect* _rect{ new SDL_Rect() };
	int _pos[2]{};
	int _height{};
	int _width{};
	SDL_Colour _colour{};

	//std::string _text{};
	Text* _text{ nullptr };

private:
	void setButtonColour();
	
	std::function<void()> _function{};
};


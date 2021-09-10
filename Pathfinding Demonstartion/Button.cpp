#include "Button.h"

Button::Button(SDL_Renderer* renderer, int pos[2], int width, int height, std::string buttonText, int fontSize, 
	std::function<void()> function)
{
	_pos[0] = pos[0];
	_pos[1] = pos[1];
	_height = height;
	_width = width;
	_rect->x = pos[0];
	_rect->y = pos[1];
	_rect->w = _width;
	_rect->h = _height;
	_function = function;
	_text = new Text(renderer, "res/arial.ttf", fontSize, buttonText, { 255, 0, 0, 255 });
}

Button::Button()
{
}

Button::~Button()
{

}

void Button::displayButton(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, _rect);
	_text->displayText(renderer, _pos[0], _pos[1]);
}

void Button::setButtonState(ButtonStates state)
{
	_buttonState = state;
	setButtonColour();
}

void Button::onClick()
{
	_function();
}

void Button::setButtonColour()
{
	switch (_buttonState)
	{
	case ButtonStates::Normal:
		_colour.r = 0;
		_colour.g = 0;
		_colour.b = 0;
		_colour.a = 255;
		break;
	case ButtonStates::Hovered:
		_colour.r = 50;
		_colour.g = 50;
		_colour.b = 50;
		_colour.a = 255;
		break;
	case ButtonStates::Clicked:
		_colour.r = 100;
		_colour.g = 100;
		_colour.b = 100;
		_colour.a = 255;
		break;
	default:
		break;
	}
}

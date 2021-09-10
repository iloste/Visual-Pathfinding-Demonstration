#include "Window.h"

Window::Window(const std::string& title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	if (init())
	{
		_initialised = true;
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit;
	SDL_Quit;
}

bool Window::init()
{
	// SDL_INIT_VIDEO because I'm not currently using anything other than the video stuff (no audio or anything)
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Failed to initialize SDL.\n";
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize SDL_ttf.\n";
		return false;
	}

	// 0 is for no flags. (flags refer to what options could be added, such as resizable).
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_width, _height, 0);

	if (_window == nullptr)
	{
		std::cerr << "Failed to create window.\n";
		return false;
	}

	//SDL_RENDERER_VSYNC would cap to 60fps, rather than ACCELERATED which does the max, I think.
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.\n";
		return false;
	}

	UIManager::getInstance().setRenderer(_renderer);
	if (!UIManager::getInstance().init())
	{
		return false;
	}
	
	return true;
}

void Window::clear() const
{
	setBackgroundColour();

	Grid::getInstance().displayGrid(_renderer);
	UIManager::getInstance().displayUI(_renderer);
	// updates the screen
	SDL_RenderPresent(_renderer);
}

void Window::setBackgroundColour() const
{
	// set colour that will be used to draw
	SDL_SetRenderDrawColor(_renderer, 200, 200, 200, 255);
	// clears the renderer with the colour (basically fills the renderer with the draw colour
	SDL_RenderClear(_renderer);
}


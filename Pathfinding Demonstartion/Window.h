#pragma once
#include "Grid.h"
#include "UIManager.h"
#include <string>
#include <SDL.h>
#include <memory>
#include <iostream>
#include <SDL_ttf.h>
class Window
{

public:
	Window(const std::string& title, int width, int height);
	~Window();

	bool inline Initialised() { return _initialised; }
	void clear() const;


private:
	bool init();
	void setBackgroundColour() const;

private:
	std::string _title;
	int _width{ 800 };
	int _height{ 600 };

	// I don't think this is needed #######################
	bool _closed{ false };
	bool _initialised{ false };


	SDL_Window* _window{ nullptr };
	SDL_Renderer* _renderer{ nullptr };

};


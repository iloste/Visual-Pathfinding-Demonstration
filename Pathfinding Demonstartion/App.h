#pragma once
#ifndef _APP_H_
#define _APP_H_	
#include <SDL.h>
#include "Window.h"


class App
{
public:
	static App& getInstance()
	{
		static App instance;
		return instance;
	}
	int execute();
	void setup();
	void OnEvent(SDL_Event* event);
	void render();

private:
	bool _running{ false };
	std::unique_ptr<Window> _window{ nullptr };

	App();

	App(App const&) = delete;
	void operator=(App const&) = delete;

};



#endif // !_APP_H_


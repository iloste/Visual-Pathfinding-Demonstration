#include "App.h"

App::App()
{

}

void App::setup()
{
	_running = true;
	_window = std::unique_ptr<Window>(new Window("Pathfinding Demo", 800, 600));

	if (!_window->Initialised())
	{
		_running = false;
	}
}

int App::execute()
{
	setup();
	SDL_Event Event;

	while (_running)
	{
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		Grid::getInstance().DisplayPathfindingProcess();

		render();
	}

	return 0;
}


void App::OnEvent(SDL_Event* Event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	// interact with UI
	if (UIManager::getInstance().mouseInteractingWithUI(x, y))
	{
		UIManager::getInstance().UIEvent(Event);
	}
	// interact with grid
	else if (Grid::getInstance().mouseIneteractinWithGrid(x, y))
	{
		switch (Event->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (Event->button.button == SDL_BUTTON_LEFT)
			{
				Grid::getInstance().setCell(Event->button.y, Event->button.x);
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (Event->type)
		{
		case SDL_QUIT:
			_running = false;
			break;
		}
	}
}

void App::render()
{
	_window->clear();

}
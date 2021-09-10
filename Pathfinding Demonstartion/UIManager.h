#pragma once
#include "Button.h"
#include <SDL.h>
#include <memory>
#include <vector>
#include <functional>

class UIManager
{

public:
	static UIManager& getInstance()
	{
		static UIManager instance;
		return instance;
	}

	bool init();
	void displayUI(SDL_Renderer* renderer);

	bool mouseOverButton(int x, int y);
	bool mouseInteractingWithUI(int x, int y);

	// the renderer should really come directly from Window, I think. Not sure though.
	void setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
	SDL_Renderer* getRenderer() { return _renderer; }

	void UIEvent(SDL_Event* event);
	void addButton(int pos[2], int width, int height, std::string buttonText, int fontSize, std::function<void()> fn);


private:
	UIManager();

	UIManager(UIManager const&) = delete;
	void operator=(UIManager const&) = delete;

	void setCurrentButton(std::shared_ptr<Button> button);
	std::shared_ptr<Button> getCurrentButton(int x, int y);

	std::vector<std::shared_ptr<Button>> _buttons{};
	//std::shared_ptr<Button> _button{ nullptr };
	SDL_Renderer* _renderer{ nullptr };

	std::shared_ptr<Button> _currentButton{ nullptr };
};


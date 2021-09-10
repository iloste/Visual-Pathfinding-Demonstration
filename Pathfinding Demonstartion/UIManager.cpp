#include "UIManager.h"

UIManager::UIManager()
{

}

bool UIManager::init()
{
	// for future development
	return true;
}

void UIManager::setCurrentButton(std::shared_ptr<Button> button)
{
	if (_currentButton != button)
	{
		if (_currentButton != nullptr)
		{
			_currentButton->setButtonState(ButtonStates::Normal);
		}

		_currentButton = button;

		if (_currentButton != nullptr)
		{
			_currentButton->setButtonState(ButtonStates::Hovered);
		}
	}
}


bool UIManager::mouseInteractingWithUI(int x, int y)
{
	// currently only set up for buttons.
	// ToDo: set up to include other UI elements
	if (mouseOverButton(x, y))
	{
		return true;
	}

	return false;
}


bool UIManager::mouseOverButton(int x, int y)
{
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (x > _buttons[i]->_pos[0] && x < _buttons[i]->_pos[0] + _buttons[i]->_width)
		{
			if (y > _buttons[i]->_pos[1] && y < _buttons[i]->_pos[1] + _buttons[i]->_height)
			{
				return true;
			}
		}
	}

	setCurrentButton(nullptr);
	return false;
}


std::shared_ptr<Button> UIManager::getCurrentButton(int x, int y)
{
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		if (x > _buttons[i]->_pos[0] && x < _buttons[i]->_pos[0] + _buttons[i]->_width)
		{
			if (y > _buttons[i]->_pos[1] && y < _buttons[i]->_pos[1] + _buttons[i]->_height)
			{
				return _buttons[i];
			}
		}
	}

	return nullptr;
}

void UIManager::addButton(int pos[2], int width, int height, std::string buttonText, int fontSize, std::function<void()> fn)
{
	_buttons.push_back(std::shared_ptr<Button>(new Button(_renderer, pos, width, height, buttonText, fontSize, fn)));
}


void UIManager::UIEvent(SDL_Event* Event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	//is mouse over button?
	if (mouseOverButton(x, y))
	{
		// get button.
		std::shared_ptr<Button> newButton = getCurrentButton(x, y);
		// is it a new button?
		if (_currentButton != nullptr && _currentButton != newButton)
		{
			// yes
			// old button no longer hovered
			_currentButton->setButtonState(ButtonStates::Normal);
		}

		_currentButton = newButton;

		if (Event->button.button == SDL_BUTTON_LEFT)
		{
			// is the lmb down?
			if (Event->type == SDL_MOUSEBUTTONDOWN)
			{
				//yes
				// button clicked
				_currentButton->setButtonState(ButtonStates::Clicked);
			}
			// is the lmb up?
			else if (Event->type == SDL_MOUSEBUTTONUP)
			{
				// yes
				// button hovered
				// do the button's action
				_currentButton->setButtonState(ButtonStates::Hovered);
				_currentButton->onClick();
			}
		}
		else
		{
			// button hovered
			_currentButton->setButtonState(ButtonStates::Hovered);
		}
	}
}


void UIManager::displayUI(SDL_Renderer* renderer)
{
	for (size_t i = 0; i < _buttons.size(); i++)
	{
		// set a new draw colour
		SDL_SetRenderDrawColor(renderer, _buttons[i]->_colour.r, _buttons[i]->_colour.g, _buttons[i]->_colour.b, _buttons[i]->_colour.a);
		//fill the rect with the draw colour
		_buttons[i]->displayButton(renderer);
	}
}

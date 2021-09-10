#include "Text.h"

Text::Text()
{

}


Text::Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
	const std::string& message, const SDL_Color& colour)
{
	_message = message;
	_texture = (loadFont(renderer, fontPath, fontSize, message, colour));
	_rect = new SDL_Rect();
	SDL_QueryTexture(_texture, nullptr, nullptr, &_rect->w, &_rect->h);
}


void Text::displayText(SDL_Renderer* renderer, int x, int y) const
{
	_rect->x = x;
	_rect->y = y;
	SDL_RenderCopy(renderer, _texture, nullptr, _rect);
}


SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string& fontPath, int fontSize, const std::string& message, const SDL_Color& colour)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
	if (!font)
	{
		std::cerr << "Failed to load font\n";
		std::cout << TTF_GetError() << "\n";
	}

	auto textSurface = TTF_RenderText_Solid(font, message.c_str(), colour);

	if (!textSurface)
	{
		std::cerr << "Failed create text surface\n";
		std::cout << TTF_GetError() << "\n";
	}

	auto textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTexture)
	{
		std::cerr << "Failed create text texture\n";
		std::cout << TTF_GetError() << "\n";
	}

	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	return textTexture;
}

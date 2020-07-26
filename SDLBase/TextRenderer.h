#pragma once



#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
class TextRenderer
{
	public:
		TextRenderer(int fontSize);
		~TextRenderer();

		void Render(SDL_Renderer* renderer, const char* message, int x, int y);

	private:
		TTF_Font* font;
		SDL_Color color;
		SDL_Surface* textSurface;
		SDL_Texture* text;
		SDL_Rect textRect;

};

#endif // TEXT_RENDERER



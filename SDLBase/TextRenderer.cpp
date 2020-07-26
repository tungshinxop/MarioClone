#include "TextRenderer.h"

TextRenderer::TextRenderer(int fontSize) {
	font = TTF_OpenFont("arial.ttf", fontSize);
	color = { 255,255,255,255 };
}

TextRenderer::~TextRenderer() {
	text = NULL;
}

void TextRenderer::Render(SDL_Renderer* renderer, const char* message, int x, int y) {
	if (text != NULL) {
		SDL_DestroyTexture(text);
	}

	//Create the surface
	textSurface = TTF_RenderText_Solid(font, message, color);

	//Pass the surface to the texture
	text = SDL_CreateTextureFromSurface(renderer, textSurface);

	//Free up the surface
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;

	//Position of the surface on the screen
	textRect.x = x;
	textRect.y = y;

	//Check for succession and render the text
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderer, text, NULL, &textRect);
}
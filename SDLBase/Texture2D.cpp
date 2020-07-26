#include "Texture2D.h"
#include <SDL_image.h>
#include "PowBlock.h"
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	mRenderer = renderer;
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

Texture2D::~Texture2D() {
	//Free up memory
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path) {
	//Remove the memory used for previous texture
	Free();

	//Load the surface
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	
	if (pSurface != NULL) {
		//Surface confirmed as created
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0, 0));

		//Set dimension
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		//Create the texture from the pixels on the surface 
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		if (mTexture == NULL) {
			cout << "Unable to create texture from surface. Error" << SDL_GetError() << endl;
		}
		else
		{		
			//Remove the surface loaded now that we have the texture
			SDL_FreeSurface(pSurface);
		}
	}
	else
	{
		cout << "Unable to create texture from surface. Error " << IMG_GetError() << endl;
	}

	//Return the texture if the process was succesful
	return mTexture !=NULL;
}

void Texture2D::Free() {
	//Check if texture exist before removing it
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;	
		mHeight = 0;
	}
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle) {
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) {
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

}

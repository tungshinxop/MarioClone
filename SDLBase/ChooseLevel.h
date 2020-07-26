#pragma once

#ifndef _CHOOSE_LEVEL
#define _CHOOSE_LEVEL

#include "Commons.h"
#include <SDL.h>
#include "GameScreen.h"
#include "TextRenderer.h"

class Texture2D;
class ChooseLevel :GameScreen {
public:
	//Function prototypes
	ChooseLevel(SDL_Renderer* renderer);
	~ChooseLevel();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:
	//Function prototypes
	bool SetUpLevel();

	Texture2D* mBackgroundTexture;
	Texture2D* mLevel1;
	Texture2D* mLevel2;
	Texture2D* mMarioGFX;

	TextRenderer* titleText;

	//Selector
	float xPos;
	float y1;
	float y2;
	float yCurrent;
};


#endif // _CHOOSE_LEVEL

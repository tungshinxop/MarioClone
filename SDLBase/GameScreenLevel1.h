#pragma once

#ifndef _GAMESCREEN_LEVEL_1
#define _GAMESCREEN_LEVEL_1

#include "Commons.h"
#include <SDL.h>
#include "GameScreen.h"
#include "TextRenderer.h"

class Texture2D;
class GameScreenLevel1 :GameScreen {
	public:
		//Function prototypes
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);

	private:
		//Function prototypes
		bool SetUpLevel();

		Texture2D* mBackgroundTexture;
		Texture2D* mPlayButton;
		Texture2D* mQuitButton;
		Texture2D* mMarioGFX;

		TextRenderer* titleText;

		//Selector
		float xPos;
		float y1;
		float y2;
		float yCurrent;
};


#endif // _GAMESCREEN_LEVEL_1

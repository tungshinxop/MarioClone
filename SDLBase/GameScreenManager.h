#pragma once

#ifndef _GAMESCREEN_MANAGER
#define _GAMESCREEN_MANAGER

#include <SDL.h>
#include "Commons.h"

class GameScreen;
class GameScreenManager {
	public:
		GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
		~GameScreenManager();

		void Render();
		void Update(float deltaTime, SDL_Event e);

		void ChangeScreen(SCREENS newScreen);

		GAMESTATE GetCurrentGameState();
		GAMESTATE GetNextGameState();
	private:
		SDL_Renderer* mRenderer;
		GameScreen* mCurrentScreen;
};

#endif // _GAMESCREEN_MANAGER


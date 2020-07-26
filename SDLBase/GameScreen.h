#pragma once

#ifndef _GAMESCREEN
#define _GAMESCREEN
#include <SDL.h>
#include "Commons.h"

class GameScreen {
	public:
		GameScreen(SDL_Renderer* renderer);
		~GameScreen();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);

		GAMESTATE GetGameState() { return currentGameState; };
		GAMESTATE GetNextGameState() { return nextGameState; };

	protected:
		SDL_Renderer* mRenderer;

		GAMESTATE currentGameState;
		GAMESTATE nextGameState;

		void SetGameState(GAMESTATE gameStateCurrent);
		void SetNextGameState(GAMESTATE gameStateNext);
};

#endif // _GAMESCREEN


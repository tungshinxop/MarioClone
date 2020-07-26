#pragma once

#ifndef _LUIGI
#define _LUIGI

#include "Character.h"

class Luigi : public Character
{
public:
	//Function prototypes
	Luigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Luigi();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int whatIsSprite;
	float mFrameDelay;
};
#endif // _LUIGI

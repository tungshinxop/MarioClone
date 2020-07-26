#pragma once

#ifndef _MARIO
#define _MARIO

#include "Character.h"
//#include "SoundEffect.h"

class Mario : public Character
{
public:
	//Function prototypes
	Mario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Mario();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int whatIsSprite;
	float mFrameDelay;


//	SoundEffect* mSoundEffect;
//	Mix_Chunk* mMix;

//	bool GetAlive() {
//		return isAlive;
//	}
//
//	void SetAlive(bool state);
//private:
//	bool isAlive;
};
#endif // _MARIO



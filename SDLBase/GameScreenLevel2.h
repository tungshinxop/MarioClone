#pragma once

#ifndef _GAMESCREEN_LEVEL_2
#define _GAMESCREEN_LEVEL_2

#include "Commons.h"
#include <SDL.h>
#include "GameScreen.h"
#include "Mario.h"
#include "Luigi.h"
#include "LevelMap.h"
#include "CharacterKoopa.h"
#include <vector>
#include "TextRenderer.h"
#include "SoundEffect.h"

class Character;
class Texture2D;
class PowBlock;

class GameScreenLevel2 :GameScreen {
public:
	//Function prototypes
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();


	void UpdatePOWBlock();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	//Function prototypes
	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();

	LevelMap* mLevelMap;
	Texture2D* mBackgroundTexture;
	Mario* myMario;
	Luigi* myLuigi;

	PowBlock* mPowBlock;
	TextRenderer* restartText;

	SoundEffect* mSoundEffect;
	Mix_Chunk* mMix;

	//Screen shake
	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;

	vector<CharacterKoopa*> mEnemies;
	float koopaTimer;
};


#endif // _GAMESCREEN_LEVEL_2

#include "ChooseLevel.h"
#include <iostream>
#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"

//Inherit from GameScreen
ChooseLevel::ChooseLevel(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();

	xPos = SCREEN_WIDTH / 2 - 140;
	y1 = SCREEN_HEIGHT / 2 - 60;
	y2 = SCREEN_HEIGHT / 2 + 40;
	yCurrent = y1;
}

ChooseLevel::~ChooseLevel() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mLevel1;
	mLevel1 = NULL;

	delete mLevel2;
	mLevel2 = NULL;

	delete mMarioGFX;
	mMarioGFX = NULL;
}

void ChooseLevel::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN:
			yCurrent = y2;
			SetNextGameState(GAME_STATE_LEVEL_2);
			break;
		case SDLK_UP:
			yCurrent = y1;
			SetNextGameState(GAME_STATE_LEVEL_1);
			break;
		}
	}
}

///OVERIDE///
void ChooseLevel::Render() {
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	titleText->Render(mRenderer, "CHOOSE LEVEL", SCREEN_WIDTH / 4 - 45, SCREEN_HEIGHT / 9);

	//Render buttons
	mLevel1->Render(Vector2D(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 80), SDL_FLIP_NONE);
	mLevel2->Render(Vector2D(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20), SDL_FLIP_NONE);

	//Render mario
	mMarioGFX->Render(Vector2D(xPos, yCurrent), SDL_FLIP_NONE);
}

bool ChooseLevel::SetUpLevel() {
	SetGameState(CHOOSE_LEVEL_STATE);
	SetNextGameState(GAME_STATE_LEVEL_1);

	//Load background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BlackBackground.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	//Load buttons texture
	mLevel1 = new Texture2D(mRenderer);
	mLevel1->LoadFromFile("Images/Level1.png");

	mLevel2 = new Texture2D(mRenderer);
	mLevel2->LoadFromFile("Images/Level2.png");

	//Load mario texture
	mMarioGFX = new Texture2D(mRenderer);
	mMarioGFX->LoadFromFile("Images/Mario.png");

	titleText = new TextRenderer(50);
}

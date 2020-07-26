#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Constants.h"
#include "Commons.h"

//Inherit from GameScreen
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();

	xPos = SCREEN_WIDTH / 2 - 140;
	y1 = SCREEN_HEIGHT / 2 - 60;
	y2 = SCREEN_HEIGHT / 2 + 40;
	yCurrent = y1;
}

GameScreenLevel1::~GameScreenLevel1(){
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mPlayButton;
	mPlayButton = NULL;
	 
	delete mQuitButton;
	mQuitButton = NULL;

	/*delete titleText;
	titleText = NULL;*/

	delete mMarioGFX;
	mMarioGFX = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	
	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			case SDLK_DOWN:
				yCurrent = y2;
				SetNextGameState(EXIT_STATE);
				break;
			case SDLK_UP:
				yCurrent = y1;
				SetNextGameState(CHOOSE_LEVEL_STATE);
				break;
		}
	}
}

///OVERIDE///
void GameScreenLevel1::Render(){
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	titleText->Render(mRenderer, "MARIO GAME!", SCREEN_WIDTH / 4 - 45, SCREEN_HEIGHT / 9);

	//Render buttons
	mPlayButton->Render(Vector2D(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 80), SDL_FLIP_NONE);
	mQuitButton->Render(Vector2D(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 +20), SDL_FLIP_NONE);

	//Render mario
	mMarioGFX->Render(Vector2D(xPos, yCurrent), SDL_FLIP_NONE);
}

bool GameScreenLevel1::SetUpLevel() {
	SetGameState(INTRO_STATE);
	SetNextGameState(CHOOSE_LEVEL_STATE);

	//Load background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BlackBackground.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	//Load buttons texture
	mPlayButton = new Texture2D(mRenderer);
	mPlayButton->LoadFromFile("Images/PlayButton.png");

	mQuitButton = new Texture2D(mRenderer);
	mQuitButton->LoadFromFile("Images/QuitButton.png");

	//Load mario texture
	mMarioGFX = new Texture2D(mRenderer);
	mMarioGFX->LoadFromFile("Images/Mario.png");

	titleText = new TextRenderer(50);

	
}
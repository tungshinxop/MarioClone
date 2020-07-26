#include <iostream>
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "RealLevel2.h"
#include "ChooseLevel.h"
#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	mRenderer = renderer;
	mCurrentScreen = NULL;

	//Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {
	mRenderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL; 
}

void GameScreenManager::Render() {
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen) {
	//Clear the old screen
	if (mCurrentScreen != NULL) {
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenLevel2* level1;
	RealLevel2* level2;
	ChooseLevel* chooseLevel;


	switch (newScreen)
	{
		case SCREEN_INTRO:
			tempScreen = new GameScreenLevel1(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen;
			tempScreen = NULL;
			break;
		case SCREEN_MENU:
			chooseLevel = new ChooseLevel(mRenderer);
			mCurrentScreen = (GameScreen*)chooseLevel;
			chooseLevel = NULL;
			break;
		case SCREEN_LEVEL1:
			level1 = new GameScreenLevel2(mRenderer);
			mCurrentScreen = (GameScreen*)level1;
			level1 = NULL;
			break;
		case SCREEN_LEVEL2:
			level2 = new RealLevel2(mRenderer);
			mCurrentScreen = (GameScreen*)level2;
			level2 = NULL;
			break;
	}
}

GAMESTATE GameScreenManager::GetCurrentGameState() {
	return mCurrentScreen->GetGameState();
}

GAMESTATE GameScreenManager::GetNextGameState() {
	return mCurrentScreen->GetNextGameState();
}
#include<iostream>
#include "GameScreen.h"
#include "Commons.h"

GameScreen::GameScreen(SDL_Renderer* renderer) {
	mRenderer = renderer;
}

GameScreen::~GameScreen() {
	mRenderer = NULL;
}


//Update and Render is empty because we will be overiding these functions in GameScreenLevel
void GameScreen::Update(float deltaTime, SDL_Event e) {

}

void GameScreen::Render() {

}

void GameScreen::SetGameState(GAMESTATE gameStateCurrent) {
	currentGameState = gameStateCurrent;
 }

void GameScreen::SetNextGameState(GAMESTATE gameStateNext) {
	nextGameState = gameStateNext;
}

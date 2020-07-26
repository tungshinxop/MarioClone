#pragma once

struct Vector2D {
	float x;
	float y;

	//Calling function 
	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}

	//Calling function with parameters
	Vector2D(float X, float Y) {
		x = X;
		y = Y;
	}
};

struct Rect2D {
	float x;
	float y;
	float width;
	float height;

	Rect2D() {
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}

	Rect2D(float X, float Y, float W, float H) {
		x = X;
		y = Y;
		width = W;
		height = H;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum GAMESTATE
{
	EXIT_STATE = 0,
	INTRO_STATE,
	CHOOSE_LEVEL_STATE,
	GAME_STATE_LEVEL_1,
	GAME_STATE_LEVEL_2
};
#pragma once

//Level dimension
#define LEVEL_WIDTH 1024
#define LEVEL_HEIGHT 416

//Screen dimension
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

//Player speed
#define MovementSpeed 100.0f
#define KOOPA_SPEED 96.0f

//Gravity
#define JUMP_FORCE_DECREMENT 550.0f
#define INITIAL_JUMP_FORCE  550.0f
#define GRAVITY 100.0f
#define GRAVITY_INCREMENT 200.0f	
#define INITIAL_JUMP_FORCE_SMALL 350.0f

//Level number of tiles
#define MAP_HEIGHT 13
#define MAP_WIDTH 16

//Tilemap
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

//Screenshake
#define SCREENSHAKE_DURATION 0.25f

//Enemies
#define INJURED_TIME 10.0f
#define TIMER_SPAWN 5.0f
#pragma once

#ifndef CHARACTER_KOOPA
#define CHARACTER_KOOPA

#include "Character.h"

class CharacterKoopa:public Character
{
	public:
		CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
		~CharacterKoopa();

		void TakeDamage();
		void Jump();
		void Render();
		void Update(float deltaTime, SDL_Event e);

		bool GetInjuredState(){
			return mInjured;
		}

		int GetCentralPositionX() {
			return ((int)(mPosition.x + (mSingleSpriteWidth * 0.5f)));
		}

		bool GetAlive() {
			return isAlive;
		}

		void SetAlive(bool state);
	private:
		void FlipRightwayUp();

		float mMovementSpeed;

		//Sprite sheet
		float mSingleSpriteWidth;
		float mSingleSpriteHeight;

		//Damage
		bool mInjured;
		float mInjuredTime;
		bool isAlive;
};

#endif // CHARACTER_KOOPA



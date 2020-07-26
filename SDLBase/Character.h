#pragma once

#ifndef _CHARACTER
#define _CHARACTER

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "SoundEffect.h"

class Texture2D;
class Character
{
	public:
		//Function prototypes
		Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
		~Character();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);

		virtual void SetPosition(Vector2D newPosition);
		virtual Vector2D GetPosition();

		virtual void AddGravity(float deltaTime);
		virtual void Jump();
		virtual bool IsJumping();
		virtual void CancelJump();

		float GetCollisionRadius();
		Rect2D GetCollisionBox();
		bool GetAlive() {
			return isAlive;
		}

		void SetAlive(bool state);
	protected:
		SDL_Renderer* mRenderer;
		Vector2D mPosition;
		Texture2D* mTexture;	

		float mCollisionRadius;

		virtual void MoveLeft(float deltaTime);
		virtual void MoveRight(float deltaTime);
		FACING mFacingDirection;

		bool mMovingLeft;
		bool mMovingRight;
		int spriteLength;


		bool mJumping;
		bool mCanJump;
		float mJumpForce;
		float mGravityForce;
	private:
		//Store LevelMap pointer
		LevelMap* mCurrentLevelMap;

		bool isAlive;

		SoundEffect* mSoundEffect;
		Mix_Chunk* mMix;
};
#endif // _CHARACTER



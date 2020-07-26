#pragma once

#ifndef POW_BLOCK
#define POW_BLOCK

#include "SDL.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock
{
	public:
		PowBlock(SDL_Renderer* renderer, LevelMap* map, Vector2D position);
		~PowBlock();

		void Render();
		Rect2D GetCollisionBox(){return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());};
		void TakeAHit();
		bool IsAvailable() { return mNumberOfHitsLeft > 0; };		
	private:
		SDL_Renderer* mRenderer;
		Vector2D mPosition;
		Texture2D* mTexture;
		LevelMap* mLevelMap;

		float mSingleSpriteWidth;
		float mSingleSpriteHeight;

		int mNumberOfHitsLeft;
};

#endif // POW_BLOCK



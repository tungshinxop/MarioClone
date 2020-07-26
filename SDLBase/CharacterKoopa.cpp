#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map) {
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	isAlive = true;
	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;//2 sprites in a row
	mSingleSpriteHeight = mTexture->GetHeight();
}


CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::TakeDamage() {
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump() {

	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::FlipRightwayUp(){
	Jump();
	if (mFacingDirection == FACING_LEFT) {
		mFacingDirection = FACING_RIGHT;
	}
	else if(mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}

	mInjured = false;

}

void CharacterKoopa::Render() {
	//Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//If injured move the left position to be the left position of the second image on the spritesheet
	if (mInjured) {
		left = mSingleSpriteWidth;
	}

	//Get the portion of the spritesheet you want to draw
	//                              {Xpos, Ypos, width of single sprite, height of single sprite}
	SDL_Rect portionOfSpritesheet = { left,0,mSingleSpriteWidth,mSingleSpriteHeight };


	//Determine where you want it to drawn
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction

	if (mFacingDirection == FACING_RIGHT) {
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::SetAlive(bool state) {
	isAlive = state;
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	//Inherit from the Character class
	Character::Update(deltaTime, e);

	//Deal with jumping first
	if (mJumping) {
		//Adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the jump force reduced to zero
		if (mJumpForce <= 0.0f) {
			mJumping = false;
		}
	}

	if (!mInjured) {
		//Not injured so move
		if (mPosition.y < 330) {
			if ((mFacingDirection == FACING_RIGHT) && (mPosition.x > SCREEN_WIDTH - mSingleSpriteWidth && mPosition.x < SCREEN_WIDTH)) {
				mFacingDirection = FACING_LEFT;
			}
			else if((mFacingDirection == FACING_LEFT) && (mPosition.x > 0 && mPosition.x < mSingleSpriteWidth))
			{
				mFacingDirection = FACING_RIGHT;
			}
		}

		if (mFacingDirection == FACING_LEFT) {
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		//Not move when injured
		mMovingLeft = false;
		mMovingRight = false;

		//Count down injured time
		mInjuredTime -= deltaTime;

		//cout << mInjuredTime << endl;

		if (mInjuredTime <= 0.0) {
			FlipRightwayUp();
		}
	}


	if (mMovingLeft) {
		mPosition.x -= mMovementSpeed * deltaTime;
	}
	else if (mMovingRight)
	{
		mPosition.x += mMovementSpeed * deltaTime;
	}
}

	
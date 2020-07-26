#include "Mario.h"
#include "Constants.h"


Mario::Mario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map) {
	/*isAlive = true;*/

	////Create instance 
	//mSoundEffect = new SoundEffect();

	imagePath = "Images/MarioAnim.png";


	//Number of sprites in the sprite sheet
	spriteLength = 8;

	//Getting the size of each sprite
	mSingleSpriteWidth = mTexture->GetWidth() / spriteLength;
	mSingleSpriteHeight = mTexture->GetHeight();
}

Mario::~Mario() {
	/*delete mMix;
	mMix = NULL;

	delete mSoundEffect;
	mSoundEffect = NULL;*/
}

//void Mario::SetAlive(bool state) {
//	isAlive = state;
//}

void Mario::Render() {

	int left = mSingleSpriteWidth * whatIsSprite;
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
}


void Mario::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);


	//Teleporting
	if ((mFacingDirection == FACING_RIGHT) && (mPosition.x > SCREEN_WIDTH - mSingleSpriteWidth && mPosition.x < SCREEN_WIDTH)) {
		mPosition.x = 0 + mSingleSpriteWidth;
	}
	else if ((mFacingDirection == FACING_LEFT) && (mPosition.x > 0 && mPosition.x < mSingleSpriteWidth))
	{
		mPosition.x = SCREEN_WIDTH - mSingleSpriteWidth;
	}

	//Animation while moving
	if (mMovingLeft == true || mMovingRight == true)
	{
		//cout << "Hello" << endl;
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			//Sop animation switching too fast
			mFrameDelay = 0.15f;

			whatIsSprite++;

			if (whatIsSprite >5)
			{
				whatIsSprite = 0;
			}
		}
	}

	//Jump animation
	if (mJumping == true)
	{
		whatIsSprite = 6;
	}
	else if (whatIsSprite >5)
	{
		whatIsSprite = 0;
	}

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

	if (GetAlive()) {
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_d:
				mMovingRight = true;
				mMovingLeft = false;
				mFacingDirection = FACING_RIGHT;
				break;
			case SDLK_a:
				mMovingRight = false;
				mMovingLeft = true;
				mFacingDirection = FACING_LEFT;
				break;
			case SDLK_w:
				Jump();
				//mMix = mSoundEffect->LoadSoundEffect("Music/Jump.wav");
				//mSoundEffect->PlaySoundEffect(mMix);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_d:
				mMovingRight = false;
				whatIsSprite = 0;
				break;
			case SDLK_a:
				mMovingLeft = false;
				whatIsSprite = 0;
				break;
			}
			break;
		}

		if (mMovingLeft) {
			MoveLeft(deltaTime);
		}
		else if (mMovingRight)
		{
			MoveRight(deltaTime);
		}
	}
	else
	{
		whatIsSprite = 7;
		mJumpForce = 300.0f;
		mJumping = true;
	}
}


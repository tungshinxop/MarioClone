#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) {

	mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;

	mRenderer = renderer;
	mPosition = startPosition;

	mFacingDirection = FACING_RIGHT;

	mMovingLeft = false;
	mMovingRight = false;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	mGravityForce = GRAVITY;

	isAlive = true;

	//Create instance 
	mSoundEffect = new SoundEffect();
	//if (!mTexture->LoadFromFile("Images/Mario.png")) {
	//	cout << "Failed to load background texture!" << endl;
	//}
}

Character::~Character() {
	mRenderer = NULL;

	delete mMix;
	mMix = NULL;

	delete mSoundEffect;
	mSoundEffect = NULL;
}

void Character::SetAlive(bool state) {
	isAlive = state;
}

void Character::Render() {
	//mTexture->Render(mPosition, SDL_FLIP_NONE);

	//Flip player
	if (mFacingDirection == FACING_RIGHT) {
		//Set to default flip
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		//Flip
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e) {
	//Collision position variables
	int centralXPosition = (int)(mPosition.x + ((mTexture->GetWidth()/8) * 0.5f)) / TILE_WIDTH; //Get the centre point of the character sprite
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT; //Get the foot position
	int headPosition = (int)(mPosition.y - (mTexture->GetHeight() /2-29)) / TILE_HEIGHT;
	int xOffsetLeft = (int)(mPosition.x + ((mTexture->GetWidth() / 8) * 0.5f) - 3) / TILE_WIDTH;
	int xOffsetRight = (int)(mPosition.x + ((mTexture->GetWidth() / 8) * 0.5f) + 3) / TILE_WIDTH;
	int footUp = (int)(mPosition.y + (mTexture->GetHeight()*0.96f)) / TILE_HEIGHT; //Get the foot position
	int footUpAndUp = (int)(mPosition.y + (mTexture->GetHeight() * 0.8f - 8)) / TILE_HEIGHT;

	//int xRightPosition = (int)(mPosition.x + mTexture->GetWidth()) / TILE_WIDTH;//Get the point next to the mario

	//int characterWidth = (int)(mTexture->GetWidth()) / TILE_WIDTH;

	//if (mCurrentLevelMap->GetTileAt(mPosition.y, characterWidth) == 1) {
	//	if (mMovingRight) {
	//		mMovingRight = false;
	//	}
	//	else if(mMovingLeft)
	//	{
	//		mMovingLeft = false;
	//	}
	//} 

	if (mMovingRight) {
		if (mCurrentLevelMap->GetTileAt(footUp, xOffsetRight) == 1) {
			//cout << "Hello right" << endl;
			mMovingRight = false;
		}
		else if(mCurrentLevelMap->GetTileAt(footUpAndUp, xOffsetRight) == 1)
		{
			mMovingRight = false;
		}
	}

	if (mMovingLeft) {
		if(mCurrentLevelMap->GetTileAt(footUp, xOffsetLeft) == 1)
		{
			mMovingLeft = false;
		}
		else if (mCurrentLevelMap->GetTileAt(footUpAndUp, xOffsetLeft) == 1)
		{
			mMovingLeft = false;
		}
	}


	if (GetAlive()) {
		if(mCurrentLevelMap->GetTileAt(headPosition, (int)(mPosition.x/TILE_WIDTH)) == 1)
		{
			CancelJump();
		}
		//Deal with gravity
		if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0) {
			AddGravity(deltaTime);
		}
		else
		{
			//Collided with ground so we can jump again
			mCanJump = true;

			//Reset gravity
			mGravityForce = GRAVITY;
		}	
	}
	else
	{
		AddGravity(deltaTime);
	}
}

void Character::SetPosition(Vector2D newPosition) {
	mPosition = newPosition;
}

Vector2D Character::GetPosition() {
	return Vector2D(mPosition.x, mPosition.y);
}

void Character::MoveLeft(float deltaTime) {
	//alter the x value of the position variable by -1
	mPosition.x -= MovementSpeed * deltaTime;
}

void Character::MoveRight(float deltaTime) {
	//alter the x value of the position variable by 1
	mPosition.x += MovementSpeed * deltaTime;
}

void Character::AddGravity(float deltaTime) {
	//Adjust postion 
	mPosition.y += mGravityForce * deltaTime;
	mGravityForce += GRAVITY_INCREMENT * deltaTime;
	mCanJump = false;
	//cout << mGravityForce << endl;	
}

bool Character::IsJumping() {
	if (mJumpForce > 0.0f) {
		return true;
	}

	return false;
}

void Character::CancelJump() {
	mJumpForce = 0;	
	mJumping = false;
}

void Character::Jump() {
	if (mCanJump) {
		if (!mJumping) {
			mJumpForce = INITIAL_JUMP_FORCE;
			mJumping = true;
			mMix = mSoundEffect->LoadSoundEffect("Music/Jump.wav");
			mSoundEffect->PlaySoundEffect(mMix);
			/*mCanJump = false;*/
		}
	}
}

float Character::GetCollisionRadius() {
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox() {
	return Rect2D(mPosition.x, mPosition.y, (mTexture->GetWidth()/ 8), mTexture->GetHeight());
}
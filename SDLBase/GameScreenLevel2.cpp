#include "GameScreenLevel2.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"

//Inherit from GameScreen
GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer) {
	mLevelMap = NULL;

	SetUpLevel();

	koopaTimer = TIMER_SPAWN;

	//Create the sound effect instance
	mSoundEffect = new SoundEffect();
}

GameScreenLevel2::~GameScreenLevel2() {
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	delete myMario;
	myMario = NULL;

	//delete myLuigi;
	//myLuigi = NULL;

	delete mMix;
	mMix = NULL;	

	delete mSoundEffect;
	mSoundEffect = NULL;

	mEnemies.clear();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {
	//-----------------------------
	//Do the screen shake if required
	//-----------------------------
	if (mScreenShake) {
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the screenshake after duration
		if (mScreenShakeTime <= 0.0f) {
			cout << "Stop screen shake" << endl;
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	//Update the player (s)
	myMario->Update(deltaTime, e);
	//myLuigi->Update(deltaTime, e);
	////Apply collision
	///*if (Collisions::Instance()->Circle(myMario, myLuigi)){
	//	cout << "Circle collision" << endl;
	//}*/
	//if(Collisions::Instance()->Box(myMario->GetCollisionBox(), myLuigi->GetCollisionBox())){
	//	
	//}

	//Update PowBlock
	UpdatePOWBlock();

	cout << koopaTimer << endl;
	if (myMario->GetAlive()) {
		//Spawn enemies
		if (koopaTimer <= 0) {
			CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
			CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

			//Reset the timer
			koopaTimer = TIMER_SPAWN;
		}
		else
		{
			koopaTimer -= deltaTime;
		}

		//Update enemies
		UpdateEnemies(deltaTime, e);
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed) {
	if (!mLevelMap) {
		cout << "Error" << endl;
	}
	mEnemies.push_back(new CharacterKoopa(mRenderer,"Images/Koopa.png",position ,mLevelMap, direction, speed));
	cout << mEnemies.size() << endl;
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!mEnemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++) {
			//Check if enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f) {
				//Is the enemy off screen to the left/right?
				if (mEnemies[i]->GetPosition().x<(float)(-mEnemies[i]->GetCollisionBox().width * 0.5f)
					|| mEnemies[i]->GetPosition().x>SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			//Now do the update
			mEnemies[i]->Update(deltaTime, e);

			//Check to see if collided with the pipe
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f)
				&& (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x >SCREEN_WIDTH - 96.0f))
			{
				//Ignore if enemies behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], myMario)) {
					//The enemies is not injured
					if (!mEnemies[i]->GetInjuredState()) {
						mMix = mSoundEffect->LoadSoundEffect("Music/MarioDeath.wav");
						mSoundEffect->PlaySoundEffect(mMix);
						myMario->SetAlive(false);
						SetNextGameState(CHOOSE_LEVEL_STATE);
						//myMario->SetState(CHARACTERSTATE_PLAYER_DEATH);
					}
					else if(mEnemies[i]->GetInjuredState())
					{
						mEnemies[i]->SetAlive(false);
						/*if (myMario->GetPosition().x > mEnemies[i]->GetCentralPositionX()) {
							cout << "On the right" << endl;
							mEnemies[i]->SetAlive(false);
						}
						else if(myMario->GetPosition().x < mEnemies[i]->GetCentralPositionX())
						{
							cout << "On the left" << endl;
							mEnemies[i]->SetAlive(false);
						}*/
					}
				}
			}

			//If enemy no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}

			//Remove enemy -1 each update
			if (enemyIndexToDelete != -1) {
				mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			}
		}
	}
}

///OVERIDE///
void GameScreenLevel2::Render() {
	//Draw enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->Render();
	}

	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//Draw PowBlock
	mPowBlock->Render();

	if (!myMario->GetAlive()) {
		restartText->Render(mRenderer, "Press Enter to return to menu", SCREEN_WIDTH / 4 , SCREEN_HEIGHT / 10);
	}

	//Draw player(s)
	myMario->Render();
	//myLuigi->Render();
}

bool GameScreenLevel2::SetUpLevel() {
	//Load background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to load background texture!" << endl;
		return false;
	}
	//Create the level map
	SetLevelMap();

	//Set up 2 bad guys
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//Set up PowBlock
	mPowBlock = new PowBlock(mRenderer, mLevelMap, Vector2D((SCREEN_WIDTH * 0.5f) - 32 * 0.5f, 260));
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	restartText = new TextRenderer(20);

	//Set up player(s)
	myMario = new Mario(mRenderer, "Images/MarioAnim.png", Vector2D(64, 330),mLevelMap);
	/*myLuigi = new Luigi(mRenderer, "Images/Luigi.png", Vector2D(120, 330), mLevelMap);*/
}


void GameScreenLevel2::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//Clear up any old map
	if (mLevelMap != NULL) {
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::DoScreenShake() {
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;	

	for  (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Jump();
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(myMario->GetCollisionBox(), mPowBlock->GetCollisionBox())) {
		if (mPowBlock->IsAvailable()) {
			cout << "Hitted Pow" << endl;				
			//Collided whilst jumping
			if (myMario->IsJumping()) {
				DoScreenShake();
				mMix = mSoundEffect->LoadSoundEffect("Music/Collision.wav");
				mSoundEffect->PlaySoundEffect(mMix);
				mPowBlock->TakeAHit();
				myMario->CancelJump();
			}
		}
	}
}
#include "SoundEffect.h"

using namespace std;
SoundEffect::SoundEffect(){
}

SoundEffect::~SoundEffect(){
	//Free memory
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

Mix_Chunk* SoundEffect::LoadSoundEffect(string path){
	mSound = Mix_LoadWAV(path.c_str());
	if (!mSound)
	{
		cout << "Monster by Irene and Seulgi is so good that I have error in my brain" << Mix_GetError() << endl;
	}
	return mSound;
}

void SoundEffect::PlaySoundEffect(Mix_Chunk* sound){
	//This receive channel, chunk and number of loops
	Mix_PlayChannel(0, sound, 0);
}
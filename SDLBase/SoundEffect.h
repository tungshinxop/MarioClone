#pragma once

#ifndef SOUND_EFFECT
#define SOUND_EFFECT

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
class SoundEffect
{
	public:
		SoundEffect();
		~SoundEffect();

		Mix_Chunk* LoadSoundEffect(std::string filePath);
		void PlaySoundEffect(Mix_Chunk* sound);

	private:
		Mix_Chunk* mSound;
};

#endif // SOUND_EFFECT



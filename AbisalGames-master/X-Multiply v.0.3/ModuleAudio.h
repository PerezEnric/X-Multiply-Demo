#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Globals.h"
#include "Module.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_MUSIC 300
#define MAX_FX 300

class ModuleAudio :public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();

	bool CleanUp();

	void PlayMusic(Mix_Music* music_to_play, int repetitions = -1);
	void PlaySoundEffect(Mix_Chunk* effect_to_play);

	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadSoundEffect(const char* path);

	void UnloadMusic(Mix_Music* music);
	void UnloadSoundEffect(Mix_Chunk* effect);

public:

	Mix_Music* songs[MAX_MUSIC];
	uint last_song = 0;

	Mix_Chunk* sound_effects[MAX_FX];
	uint last_effect = 0;

};
#endif



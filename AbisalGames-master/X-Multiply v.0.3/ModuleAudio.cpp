#include "ModuleAudio.h"
#include "SDL_mixer\include\SDL_mixer.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio()
{
	for (uint i = 0; i < MAX_MUSIC; ++i)
		songs[i] = nullptr;

	for (uint i = 0; i < MAX_FX; ++i)
		sound_effects[i] = nullptr;
}

ModuleAudio::~ModuleAudio()
{
}

bool ModuleAudio::Init()
{
	bool ret = true;

	LOG("Init Audio Module.........");

	if (Mix_Init(MIX_INIT_OGG) < 0)
	{
		LOG("Audio Module can't be initialized: %s/n", Mix_GetError());
		ret = false;
	}
	else
	{
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		{
			LOG("Audio Module can't open: %s/n", Mix_GetError());
			ret = false;
		}
	}

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Cleaning Audio Module");

	for (uint i = 0; i < MAX_MUSIC; ++i)
	{
		if (songs[i] != nullptr)
			Mix_FreeMusic(songs[i]);
	}

	for (uint i = 0; i < MAX_FX; ++i)
	{
		if (sound_effects[i] != nullptr)
			Mix_FreeChunk(sound_effects[i]);
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

void ModuleAudio::PlayMusic(Mix_Music * music_to_play, int repetitions)
{
	Mix_PlayMusic(music_to_play, repetitions);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
}

void ModuleAudio::PlaySoundEffect(Mix_Chunk * effect_to_play)
{
	Mix_PlayChannel(-1, effect_to_play, 0);
}

Mix_Music * const ModuleAudio::LoadMusic(const char * path)
{
	Mix_Music* music = nullptr;

	if (last_song < MAX_MUSIC)
	{
		music = Mix_LoadMUS(path);

		if (music == nullptr)
		{
			LOG("Couldn't load song with path: %s. Error: %s.", path, Mix_GetError());
		}
		else
		{
			songs[last_song++] = music;
		}
	}

	return music;
}

Mix_Chunk * const ModuleAudio::LoadSoundEffect(const char * path)
{
	Mix_Chunk* effect = nullptr;

	if (last_effect < MAX_FX)
	{
		effect = Mix_LoadWAV(path);

		if (effect == nullptr)
		{
			LOG("Couldn't load sound effect with path: %s. Error: %s.", path, Mix_GetError());
		}
		else
		{
			sound_effects[last_effect++] = effect;
		}
	}

	return effect;
}

void ModuleAudio::UnloadMusic(Mix_Music * music)
{
	for (uint i = 0; i < last_song; ++i)
	{
		if (songs[i] == music)
		{
			Mix_FreeMusic(music);
			songs[i] = nullptr;
			break;
		}
	}
}

void ModuleAudio::UnloadSoundEffect(Mix_Chunk * effect)
{
	for (uint i = 0; i < last_effect; ++i)
	{
		if (sound_effects[i] == effect)
		{
			Mix_FreeChunk(effect);
			sound_effects[i] = nullptr;
			break;
		}
	}
}

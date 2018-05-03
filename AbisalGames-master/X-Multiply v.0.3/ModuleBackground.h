#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")
struct SDL_Texture;
struct Rect;
struct _Mix_Music;
struct Mix_Chunk;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	bool inject;
	bool move;
	int cont = 0;
	int xinject = 75;
	int yinject = -100;
	void animinject();
	bool win = false;
public:
	
	Mix_Music* firstlvlmusic = nullptr;
	Mix_Chunk* spaceshipdrop = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicswall = nullptr;
	SDL_Texture* graphicsinjection = nullptr;
	SDL_Texture* ui = nullptr;
	Animation back;
	Animation injectionanim;
	SDL_Rect wall;
	SDL_Rect background;
	SDL_Rect injection;
};

#endif
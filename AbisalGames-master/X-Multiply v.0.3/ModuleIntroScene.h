#ifndef __ModuleIntroScene_H__
#define __ModuleIntroScene_H__

#include "Module.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleIntroScene : public Module
{
public:
	ModuleIntroScene();
	~ModuleIntroScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	bool flag = false;
	SDL_Texture* introBackground = nullptr;
	Mix_Music* intro_music = nullptr;
	SDL_Rect game_title;
	SDL_Rect game_company;
};
#endif

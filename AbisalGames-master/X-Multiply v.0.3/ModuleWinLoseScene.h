#ifndef __ModuleWinLoseScene_H__
#define __ModuleWinLoseScene_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleWinLoseScene : public Module
{
public:
	ModuleWinLoseScene();
	~ModuleWinLoseScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* lose_screen = nullptr;
	Mix_Music* game_over_music = nullptr;
	Mix_Music* win_music = nullptr;
	SDL_Rect G;
	SDL_Rect A;
	SDL_Rect M;
	SDL_Rect E;
	SDL_Rect O;
	SDL_Rect V;
	SDL_Rect E2;
	SDL_Rect R;
	SDL_Rect C;
	SDL_Rect L;
	SDL_Rect S;
	SDL_Rect T;
	SDL_Rect ONE;
	SDL_Rect D;
	SDL_Rect B;
	SDL_Rect N;
	SDL_Rect U;
	SDL_Rect ZERO;

	SDL_Rect camera;
	iPoint position;
};

#endif

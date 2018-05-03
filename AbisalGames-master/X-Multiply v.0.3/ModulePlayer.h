#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:
	Mix_Chunk* shot_particle = nullptr;
	Mix_Chunk* player_death = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation* current_animation = nullptr;
	Animation up;
	Animation down;
	iPoint position;
	Collider* col;
	bool destroyed = false;
	int live = 3;
	int speed = 1;
	int cameraback = 0;
	int font_score = -1;
	bool turbo = false;
	bool bomb = false;
	bool tentacles = false;
	bool tentacles_front = false;
	bool tentacles_mid = false;
	bool tentacles_back = false;
	bool tentacles_up = false;
	bool tentacles_down = false;
	char text[10];
	int cd = 0;
	uint score = 0;
	int points = 0;
	int limitx = 15;
	float limity = 0;
};

#endif

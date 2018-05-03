
#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_Ball.h"
#include "Enemy_Ball2.h"
#include "Enemy_LittleShrimp.h"
#include "Enemy_Anemone.h"
#include "Enemy_PU.h"
#include "PowerUp_SpeedUp.h"
#include "Bomb_PowerUp.h"
#include "Tentacles_PowerUp.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define MAX_ENEMIES 100

// TODO 2: Add a new enemy: Brown Cookies!

// TODO 3: Have the Brown Cookies describe a path in the screen

// TODO 4: Create a new enemy type: the Mech

enum ENEMY_TYPES
{
	NO_TYPE,
	BALL,
	BALL2,
	SHRIMP,
	ANEMONE,
	PU,
	SPEEDUP,
	BOMB,
	TENTACLES,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;

};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y);
	uint points = 0;
	bool lets;
	bool letb;
	bool lett;
	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	
private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__

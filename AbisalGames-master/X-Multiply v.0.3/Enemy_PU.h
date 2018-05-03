#ifndef __Enemy_PU_H__
#define __Enemy_PU_H__

#include "Enemy.h"

class Enemy_PU : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly_PU;
	int points = 1000;

public:
	
	Enemy_PU(int x, int y);
	~Enemy_PU() {};
	void Move();
	void OnCollision(Collider* collider);
	bool CleanUp();
};

#endif // __Enemy_PU_H__



#ifndef __Enemy_LittleShrimp_H__
#define __Enemy_LittleShrimp_H__

#include "Enemy.h"

class Enemy_LittleShrimp : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly_shrimp;
	int cd = 0;
	int points = 400;

public:
	
	Enemy_LittleShrimp(int x, int y);
	~Enemy_LittleShrimp() {};
	void Move();
	void OnCollision(Collider* collider);
	bool CleanUp();
};

#endif //  __Enemy_LittleShrimp_H__


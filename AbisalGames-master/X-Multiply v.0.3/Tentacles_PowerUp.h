#ifndef __Tentacles_PowerUp_H__
#define __Tentacles_PowerUp_H__
#include "Enemy.h"

class Tentacles_PowerUp : public Enemy
{
private:
	Animation tentacleanim;
	int original_y = 0;

public:
	Mix_Chunk * powerup_sound = nullptr;
	Tentacles_PowerUp(int x, int y);
	~Tentacles_PowerUp() {};
	void OnCollision(Collider* collider);
	void Move();
	bool CleanUp();

};

#endif


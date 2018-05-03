#ifndef __PowerUp_SpeedUp_H__
#define __PowerUp_SpeedUp_H__
#include "Enemy.h"

class PowerUp_SpeedUp : public Enemy
{
private:
	int original_y = 0;
	Animation fly;
	

public:
	Mix_Chunk* boost_sound = nullptr;
	PowerUp_SpeedUp(int x, int y);
	~PowerUp_SpeedUp() {};
	void Move();
	void OnCollision(Collider* collider);
	bool CleanUp();

};

#endif //  __PowerUp_SpeedUp_H__

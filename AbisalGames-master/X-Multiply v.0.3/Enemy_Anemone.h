#ifndef __Enemy_Anemone_H__
#define __Enemy_Anemone_H__

#include "Enemy.h"

class Enemy_Anemone : public Enemy
{
private:

	Animation anem;

public:

	Enemy_Anemone(int x, int y);
	~Enemy_Anemone() {};
	void Move();
	void OnCollision(Collider* collider);
	int cd = 0;
	int points = 600;
	bool CleanUp();
	int live = 3;
};

#endif //  __Enemy_Anemone_H__
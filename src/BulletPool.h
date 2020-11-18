#pragma once
#ifndef __BULLETPOOL__
#define __BULLETPOOL__
#include "Bullet.h"
#include <vector>

class BulletPool
{
public:
	BulletPool(int);
	~BulletPool();

	Bullet* Spawn();
	void Despawn(Bullet*);
	std::vector<Bullet*> all;
private:
	std::vector<Bullet*> inactive;
	std::vector<Bullet*> active;
};
#endif /* defined (__BULLETPOOL__) */

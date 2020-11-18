#pragma once
#include "Bullet.h"
#include "BulletPool.h"
class BulletManager {
private:
	BulletPool* m_pPool;
	float spawnTime = 3.0f;
	float timer;
public:
	void update();
};

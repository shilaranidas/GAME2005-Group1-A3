#include "BulletPool.h"
#include <iostream>

BulletPool::BulletPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		Bullet* bullet = new Bullet();
		inactive.push_back(bullet);
		all.push_back(bullet);
	}
	std::cout << "Bullet pool created with size " << size << "\n";
}
BulletPool::~BulletPool() = default;
Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size() > 0)
	{
		bullet = inactive.back();
		bullet->Reset();
		bullet->active = true;
		inactive.pop_back();
		active.push_back(bullet);
		activeColliding.push_back(false);
		///activeColliding[active.size()-1] = false;
		std::cout << "SPAWNED \n Active count " << active.size() << "\n";
	}
	else
	{
		std::cout << "Error bullet could not be spawned. Max bullets reached\n";
	}
	return bullet;
}

void BulletPool::Despawn(Bullet* bullet)
{
	bullet->active = false;
	inactive.push_back(bullet);
	
	std::vector<bool>::iterator myBoolIter = activeColliding.begin();
	for (std::vector<Bullet*>::iterator myIter = active.begin(); myIter != active.end(); myIter++)
	{
		
		if (*myIter == bullet)
		{
			active.erase(myIter);
			activeColliding.erase(myBoolIter);
			//activeColliding[i]
			//activeColliding.erase(activeColliding.begin()+i);
			std::cout << "Bullet despawned.\nActive: " << active.size() << "\n";
			std::cout << "despawned \n inactive count " << inactive.size() << "\n";
			return;
		}
		myBoolIter++;
	}
}

void BulletPool::ResetAll()
{
	std::vector<bool>::iterator myBoolIter = activeColliding.begin();
	for (std::vector<Bullet*>::iterator myIter = active.begin(); myIter != active.end(); myIter++)
	{
		//Despawn(*myIter);
		//inactive.push_back(*myIter);
		(*myIter)->active = false;
		inactive.push_back(*myIter);
		active.erase(myIter);
		activeColliding.erase(myBoolIter);
		//myBoolIter++;
	}
	
}
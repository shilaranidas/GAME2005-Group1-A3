#pragma once
#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__

// core libraries
#include <iostream>

#include "GameObject.h"
#include "ship.h"
#include <GLM/gtx/norm.hpp>
#include "SoundManager.h"
#include "ball.h"
#include "Brick.h"
#include "Util.h"
class CollisionManager
{
public:
	static int squaredDistance(glm::vec2 p1, glm::vec2 p2);
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);

	static bool AABBCheck(GameObject* object1, GameObject* object2);

	static bool AABBCheck1(GameObject* object1, GameObject* object2, std::vector<bool> activeColliding, int i);
	static bool lineLineCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);
	static bool lineRectCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 rec_start, float rect_width, float rect_height);
	//static bool lineCircleCheck(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 circle_centre, int circle_radius);
	static int minSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end);
	static bool lineAABBCheck(Ship* object1, GameObject* object2);

	static int circleAABBsquaredDistance(glm::vec2 circle_centre, int circle_radius, glm::vec2 box_start, int box_width, int box_height);
	static bool circleAABBCheck(GameObject* object1, GameObject* object2);
	static bool circleLineCheck(GameObject* object1, glm::vec2 line1_start, glm::vec2 line1_end);

	static bool pointRectCheck(glm::vec2 point, glm::vec2 rect_start, float rect_width, float rect_height);
	
private:
	CollisionManager();
	~CollisionManager();
};

#endif /* defined (__COLLISION_MANAGER__) */
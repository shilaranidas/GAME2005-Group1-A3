#pragma once
#ifndef __BALL__
#define __BALL__
#include "Sprite.h"


class Ball : public Sprite
{
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
	void m_checkBounds();
	void m_move();
	void reset();
	void changeShape();
	//void addForce(glm::vec2 Amount);
	//void move();

//	bool doesUpdate = false;
	bool isActive = false;
	//float m_gravity = 9.8f;
	float m_PPM = 1.0f;
	float m_WallFriction = 0.9f;
	float m_Mass = 1.0f;
	int Shape = 0;//0 for circle, 1 for triangle, 2 for square, 3 for pentagon
	//float Mass;
	//float nextPosition;
//	bool showWire;

	//glm::vec2 Force;
	//void RandomPos();

};

#endif
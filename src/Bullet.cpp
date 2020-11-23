#include "Bullet.h"
//#include "glm/gtx/string_cast.hpp"
//#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
//#include "Util.h"
//#include "Game.h"

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/bulletM.png", "bullet");

	auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(0.0f, -getHeight());
	
	setType(BULLET);
	setCollisionShape(RECTANGLE);
	Reset();
	/*nextPosition = 0;
	pixelsPerMeter = 1;
	Gravity = 9.8f;
	Mass = 1;
	showWire = true;*/
}


Bullet::~Bullet()
= default;

void Bullet::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	//float bw = getWidth();
	//float bh = getHeight();
	//if (showWire)
	//{
	//	glm::vec2 bpos[4];
	//	// Bottom-Left
	//	bpos[0] = glm::vec2(x - bw / 4, y + bh / 2);
	//	// Bottom-Right
	//	bpos[1] = glm::vec2(x + bw / 3, y + bh / 2);
	//	// Top-Left
	//	bpos[2] = glm::vec2(x - bw / 4, y - bh / 2);
	//	// Top-Right
	//	bpos[3] = glm::vec2(x + bw / 3, y - bh / 2);
	//	// Bottom
	//	Util::DrawLine(bpos[0], bpos[1]);
	//	// Top
	//	Util::DrawLine(bpos[2], bpos[3]);
	//	// Left
	//	Util::DrawLine(bpos[0], bpos[2]);
	//	// Right
	//	Util::DrawLine(bpos[1], bpos[3]);
	//}
	// draw the Bullet
	TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
	//Util::DrawCapsule(getTransform()->position , getWidth(), getHeight());
	Util::DrawRect(getTransform()->position - glm::vec2(getWidth() * 0.5f, getHeight() * 0.5f), getWidth(), getHeight());
}

 
void Bullet::update()
{
	//if (doesUpdate) move();
	if (active) {
		float deltaTime = 1.0f / 60.0f;
		//getRigidBody()->acceleration = glm::vec2(0, 9.8 * 3.0);
		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
		getTransform()->position += getRigidBody()->velocity * deltaTime * m_PPM;
	}
	//else
		//getRigidBody()->velocity= glm::vec2(0.0f, 0.0f);
}

void Bullet::clean()
{

}
void Bullet::Reset()
{
	getRigidBody()->acceleration = glm::vec2(0.0f, m_gravity);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
}
//void Bullet::addForce(glm::vec2 Amount)
//{
//	Force += Amount;
//}
//
//void Bullet::move()
//{
//	float deltaTime = 1.0f / Config::FPS;
//
//	if (nextPosition != 0)
//	{
//		getTransform()->position.y = nextPosition;
//		nextPosition = 0;
//	}
//	else
//	{
//		getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
//		getTransform()->position += getRigidBody()->velocity * deltaTime * pixelsPerMeter;
//	}
//
//}
//
//void Bullet::RandomPos()
//{
//	float randomPosX = rand() % Config::SCREEN_WIDTH - getWidth();
//	getTransform()->position.x = randomPosX;
//	getTransform()->position.y = 0;
//	getRigidBody()->acceleration.y = Gravity;
//	getRigidBody()->velocity.y = getRigidBody()->acceleration.y;
//}
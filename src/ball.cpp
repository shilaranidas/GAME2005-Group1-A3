#include "ball.h"
#include "Bullet.h"
//#include "glm/gtx/string_cast.hpp"
//#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
//#include "Util.h"
//#include "Game.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "ball");

	auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(size.x);
	setHeight(size.y);

	//getTransform()->position = glm::vec2(700.0f, 0.0f);

	setType(BALL);
	setCollisionShape(RECTANGLE);
	reset();
	/*nextPosition = 0;
	pixelsPerMeter = 1;
	Gravity = 9.8f;
	Mass = 1;
	showWire = true;*/
}


Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	

	// draw the Bullet
	TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
	//Util::DrawCapsule(getTransform()->position , getWidth(), getHeight());
	Util::DrawRect(getTransform()->position - glm::vec2(getWidth() * 0.5f, getHeight() * 0.5f), getWidth(), getHeight());
}


void Ball::update()
{
	////if (doesUpdate) move();
	//if (active) {
	//	float deltaTime = 1.0f / 60.0f;
	//	//getRigidBody()->acceleration = glm::vec2(0, 9.8 * 3.0);
	//	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	//	getTransform()->position += getRigidBody()->velocity * deltaTime * m_PPM;
	//}
	////else
	//	//getRigidBody()->velocity= glm::vec2(0.0f, 0.0f);
	m_move();
	m_checkBounds();
}
void Ball::m_move()
{
	glm::vec2 newPosition = getTransform()->position + getRigidBody()->velocity * 2.0f;
	getTransform()->position=newPosition;
}
void Ball::clean()
{

}
void Ball::m_checkBounds()
{
	if ((getTransform()->position.y > 600.0f + getHeight() * 0.5f) || // bottom 
		(getTransform()->position.y < -getHeight() * 0.5f) || // top
		(getTransform()->position.x > 800.0f + getWidth() * 0.5) || // right
		(getTransform()->position.x < -getWidth() * 0.5f)) // left
	{
		reset();
	}
}
//void Ball::Reset()
//{
//	//getRigidBody()->acceleration = glm::vec2(0.0f, m_gravity);
//	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
//	getRigidBody()->isColliding = false;
//}
void Ball::reset()
{
	int d4 = ceil(Util::RandomRange(0.0, 4.0));

	switch (d4)
	{
	case 1: // top
		getTransform()->position=glm::vec2(Util::RandomRange(getWidth() * 0.5f, 800.0f - getWidth()), -getHeight() * 0.5f);
		getRigidBody()->velocity=glm::vec2(Util::RandomRange(-1.0f, 1.0f), 1.0f);
		break;
	case 2: // right
		getTransform()->position=glm::vec2(800.0f + getWidth() * 0.5f, Util::RandomRange(getHeight() * 0.5f, 600.0f - getHeight()));
		getRigidBody()->velocity=glm::vec2(-1.0f, Util::RandomRange(-1.0f, 1.0f));
		break;
	case 3: // bottom
		getTransform()->position=glm::vec2(Util::RandomRange(getWidth() * 0.5f, 800.0f - getWidth()), 600.0f + getHeight() * 0.5f);
		getRigidBody()->velocity=glm::vec2(Util::RandomRange(-1.0f, 1.0f), -1.0f);
		break;
	case 4: // left
		getTransform()->position=glm::vec2(-getWidth() * 0.5f, Util::RandomRange(getHeight() * 0.5f, 600.0f - getHeight()));
		getRigidBody()->velocity=glm::vec2(1.0f, Util::RandomRange(-1.0f, 1.0f));
		break;
	}

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
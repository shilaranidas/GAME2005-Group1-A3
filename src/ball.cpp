#include "ball.h"
#include "Bullet.h"
//#include "glm/gtx/string_cast.hpp"
//#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "SoundManager.h"
//#include "Util.h"
//#include "Game.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/circle.png", "circle");
	TextureManager::Instance()->load("../Assets/textures/square.png", "square");
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "triangle");
	TextureManager::Instance()->load("../Assets/textures/pentagon.png", "pentagon");

	auto size = TextureManager::Instance()->getTextureSize("circle");
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

void Ball::changeShape()
{
	//0 for circle, 1 for triangle, 2 for square, 3 for pentagon
	if (Shape == 0)
	{	
		auto size = TextureManager::Instance()->getTextureSize("circle");
		setWidth(size.x);
		setHeight(size.y);
	}
	else if (Shape == 1)
	{
		auto size = TextureManager::Instance()->getTextureSize("triangle");
		setWidth(size.x);
		setHeight(size.y);
	}
	else if (Shape == 2)
	{
		auto size = TextureManager::Instance()->getTextureSize("square");
		setWidth(size.x);
		setHeight(size.y);
	}
	else if (Shape == 3)
	{
		auto size = TextureManager::Instance()->getTextureSize("pentagon");
		setWidth(size.x);
		setHeight(size.y);
	}
}
void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	

	// draw the Bullet
	//TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
	if (Shape == 0)
	{
		
		TextureManager::Instance()->draw("circle", x, y, 0, 255, true);
	}
	else if (Shape == 1)
	{
		
		TextureManager::Instance()->draw("triangle", x, y, 0, 255, true);
	}
	else if (Shape == 2)
	{
		
		TextureManager::Instance()->draw("square", x, y, 0, 255, true);
	}
	else if (Shape == 3)
	{
		
		TextureManager::Instance()->draw("pentagon", x, y, 0, 255, true);
	}
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
	if (isActive)
	{
		//getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
		glm::vec2 newPosition = getTransform()->position + getRigidBody()->velocity*m_PPM;
		getTransform()->position = newPosition;
	}
}
void Ball::clean()
{

}
void Ball::m_checkBounds()
{
	
	auto velocityX = getRigidBody()->velocity.x;
	auto velocityY = getRigidBody()->velocity.y;
	if ((getTransform()->position.y > Config::SCREEN_HEIGHT - getHeight() * 0.5f))  // bottom 
	{
		SoundManager::Instance().playSound("bounce", 0);
		getTransform()->position.y = Config::SCREEN_HEIGHT - getHeight() * 0.5f;
			getRigidBody()->velocity = glm::vec2(velocityX, -velocityY * m_WallFriction);
			//std::cout << "in y"<<std::endl;
	}
	else if	((getTransform()->position.y < getHeight()*0.5f ))  // top
	{
		SoundManager::Instance().playSound("bounce", 0);
		getTransform()->position.y =  getHeight() * 0.5f;
		getRigidBody()->velocity = glm::vec2(velocityX, -velocityY*m_WallFriction);
		//std::cout << "in y"<<std::endl;
	}
	else if	((getTransform()->position.x > Config::SCREEN_WIDTH -getWidth() * 0.5))  // right
	{
		SoundManager::Instance().playSound("bounce", 0);
		getTransform()->position.x = Config::SCREEN_WIDTH - getWidth() * 0.5;
			getRigidBody()->velocity = glm::vec2(-velocityX * m_WallFriction, velocityY);
			//reset();
			//std::cout << "in x" << std::endl;
	}
	else if	((getTransform()->position.x < getWidth() * 0.5f)) // left
	{
		SoundManager::Instance().playSound("bounce", 0);
		getTransform()->position.x = getWidth() * 0.5f;
		getRigidBody()->velocity = glm::vec2(-velocityX * m_WallFriction, velocityY);
		//reset();
		//std::cout << "in x" << std::endl;
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
	int d4 = 2;//ceil(Util::RandomRange(0.0, 4.0));

	switch (d4)
	{
	case 1: // top
		getTransform()->position=glm::vec2(Util::RandomRange(getWidth() , Config::SCREEN_WIDTH - getWidth()), getHeight() );
		getRigidBody()->velocity=glm::vec2(Util::RandomRange(-1.0f, 1.0f), 1.0f);
		break;
	case 2: // right
		getTransform()->position=glm::vec2(Config::SCREEN_WIDTH - getWidth() , Util::RandomRange(getHeight() , Config::SCREEN_HEIGHT - getHeight()));
		getRigidBody()->velocity=glm::vec2(-1.0f, Util::RandomRange(-1.0f, 1.0f));
		break;
	case 3: // bottom
		getTransform()->position=glm::vec2(Util::RandomRange(getWidth() , Config::SCREEN_WIDTH - getWidth()), Config::SCREEN_HEIGHT - getHeight() );
		getRigidBody()->velocity=glm::vec2(Util::RandomRange(-1.0f, 1.0f), -1.0f);
		break;
	case 4: // left
		getTransform()->position=glm::vec2(getWidth() , Util::RandomRange(getHeight() , Config::SCREEN_HEIGHT - getHeight()));	
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
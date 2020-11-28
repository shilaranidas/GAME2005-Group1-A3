#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Target.h"
#include "ball.h"
#include "Brick.h"

class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void reset();
	void changeLabel();
private:
	/*Label* m_pStartLabel;
	Label* m_pInstructionsLabel;*/

	// Ship Stuff
	Brick* m_pBrick;
//	MoveState m_moveState;
	glm::vec2 m_speedFactor;
	float m_PPM = 1.0f; // pixels per meter - scale
	
	// Bullet Stuff
	Ball* m_pBall;
	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;




	Label* m_pInstructionsLabel;
	//std::vector<Ball*> m_pBalls;

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	
	void StartSimulation();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;

	// Physics Variables
	float m_gravity = 9.8f;

	glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_velocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 m_acceleration = glm::vec2(0.0f, 0.0f);
	Label* lblBallMass;
	Label* lblBrickMass;
	Label* lblBallVel;
	Label* lblBrickVel;
	Label* lblWallFriction;
	//float m_BallMass = 0.0f;
	//float m_BrickMass = 1.0f;
	//float m_WallFriction = 0.9f;
	// Physics functions
	//void m_move();
};

#endif /* defined (__END_SCENE__) */
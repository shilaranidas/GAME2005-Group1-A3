#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Target.h"
#include "ship.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	void changeLabel();
	
	void Calculation();
	void reset();
	
private:
	// IMGUI Function
	void GUI_Function() ;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	//Plane* m_pPlaneSprite;
	//Player* m_pPlayer;
	//Target* m_pLoot;
	Ship* m_pStormtrooper;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	
	
	
	
	Label* m_pInstructionsLabel;
	//mass, position, velocity, acceleration
	Label* m_pMass;
	
	Label* m_pVel;
	Label* m_pAcce;

	Label* m_pForce;

	
	int fl = 510.0f;


	// Physics Variables
	

	float m_PPM = 5.0f; // pixels per meter - scale
	


	int m_distance = 485;
	//float m_Force = 0.0f;
	
	
	


	

	






	float m_totalTime=0.0f;
};

#endif /* defined (__PLAY_SCENE__) */
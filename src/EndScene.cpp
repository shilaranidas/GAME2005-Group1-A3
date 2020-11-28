#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "Renderer.h"
#include "imgui.h"
#include "imgui_sdl.h"
#include "Util.h"
EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw("bg", Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, 0, 255, true);

	/*m_pStartLabel->draw();
	m_pInstructionsLabel->draw();*/

	//m_pBrick->draw();
	//m_pPlanet->draw();
	//m_pMine->draw();

	//for (auto ball : m_pBalls)
	//{
	//if (m_pBall != NULL)
		m_pBall->draw();
//	}
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	// ImGui Rendering section - DO NOT MOVE OR DELETE
	if (EventManager::Instance().isIMGUIActive())
	{
		m_updateUI();
		

		// debug collider shapes
	/*	Util::DrawLine(glm::vec2(0, 0), glm::vec2(0, Config::SCREEN_HEIGHT));
		Util::DrawLine(glm::vec2(0, 0), glm::vec2(Config::SCREEN_WIDTH, 0));
		Util::DrawLine(glm::vec2(0, Config::SCREEN_HEIGHT-1), glm::vec2(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT-1));
		Util::DrawLine(glm::vec2(Config::SCREEN_WIDTH-1, 0), glm::vec2(Config::SCREEN_WIDTH-1, Config::SCREEN_HEIGHT));*/
		//if (m_pBall != NULL)
		//{
			Util::DrawRect(m_pBall->getTransform()->position - glm::vec2(m_pBall->getWidth() * 0.5f, m_pBall->getHeight() * 0.5f), m_pBall->getWidth(), m_pBall->getHeight());
			Util::DrawLine(m_pBall->getTransform()->position, m_pBrick->getTransform()->position);
		//}

		//if (m_pBrick != NULL)
			Util::DrawRect(m_pBrick->getTransform()->position - glm::vec2(m_pBrick->getWidth() * 0.5f, m_pBrick->getHeight() * 0.5f), m_pBrick->getWidth(), m_pBrick->getHeight());
		//Util::DrawRect(m_pPlanet->getPosition() - glm::vec2(m_pPlanet->getWidth() * 0.5f, m_pPlanet->getHeight() *0.5f), m_pPlanet->getWidth(), m_pPlanet->getHeight());
		//Util::DrawRect(m_pMine->getPosition() - glm::vec2(m_pMine->getWidth() * 0.5f, m_pMine->getHeight() *0.5f), m_pMine->getWidth(), m_pMine->getHeight());


		//Util::DrawCircle(m_pShip->getPosition(), std::max(m_pShip->getWidth() * 0.5, m_pShip->getHeight() * 0.5));
		//Util::DrawCircle(m_pPlanet->getPosition(), std::max(m_pPlanet->getWidth() * 0.5, m_pPlanet->getHeight() * 0.5));
		//Util::DrawCircle(m_pMine->getPosition(), std::max(m_pMine->getWidth() * 0.5, m_pMine->getHeight() * 0.5));
	}
}

void EndScene::update()
{
	updateDisplayList();
	//m_move();
	m_pBrick->update();
	//m_pPlanet->update();
	//m_pMine->update();
	//for (auto ball : m_pBalls)
	//{
	if (m_pBall->isActive)
		m_pBall->update();
	if (m_pBrick->isActive && m_pBall->isActive)
	{
		CollisionManager::circleAABBCheck(m_pBall, m_pBrick);
	}
	/*
	Util::DrawLine(glm::vec2(0, 0), glm::vec2(0, Config::SCREEN_HEIGHT));
		Util::DrawLine(glm::vec2(0, 0), glm::vec2(Config::SCREEN_WIDTH, 0));
		Util::DrawLine(glm::vec2(0, Config::SCREEN_HEIGHT-1), glm::vec2(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT-1));
		Util::DrawLine(glm::vec2(Config::SCREEN_WIDTH-1, 0), glm::vec2(Config::SCREEN_WIDTH-1, Config::SCREEN_HEIGHT));
	*/
	//const auto p1 = m_pBall->getTransform()->position - glm::vec2(m_pBall->getWidth() * 0.5f, m_pBall->getHeight() * 0.5f);
	//CollisionManager::lineRectCheck(glm::vec2(0, 0), glm::vec2(0, Config::SCREEN_HEIGHT), p1, m_pBall->getWidth(), m_pBall->getHeight());
	
	//CollisionManager::circleLineCheck(m_pBall, glm::vec2(0, 0), glm::vec2(0, Config::SCREEN_HEIGHT));
	//	CollisionManager::circleAABBCheck(m_pBall, m_pShip);
	//}

	//CollisionManager::squaredRadiusCheck(m_pShip, m_pPlanet);
	//CollisionManager::squaredRadiusCheck(m_pShip, m_pMine);

	//CollisionManager::AABBCheck(m_pShip, m_pPlanet);
	//CollisionManager::AABBCheck(m_pShip, m_pMine);

	//CollisionManager::circleAABBCheck(m_pShip, m_pPlanet);
	//CollisionManager::circleAABBCheck(m_pShip, m_pMine);


	
}

void EndScene::clean()
{
	/*delete m_pStartLabel;
	delete m_pInstructionsLabel;*/

	//delete m_pBrick;

	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			/*if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}*/
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		/*if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}*/
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
	
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	
}

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/bg.png", "bg");
	
	SoundManager::Instance().load(
		"../Assets/audio/yay.ogg",
		"yay", SOUND_SFX);
	SoundManager::Instance().load(
		"../Assets/audio/thunder.ogg",
		"thunder", SOUND_SFX);
	SoundManager::Instance().load(
		"../Assets/audio/bounce.ogg",
		"bounce", SOUND_SFX);

	m_position = glm::vec2(400.0f, 500.0f);
	m_pBrick = new Brick();
	m_pBrick->getTransform()->position = m_position;
	addChild(m_pBrick);
	m_pBall = new Ball();
	m_pBall->isActive = false;
	m_pBall->getTransform()->position = glm::vec2(300,300);
	addChild(m_pBall);
	m_velocity = glm::vec2(0.0, 0.0); //glm::vec2(1.0f, m_velocity.y);
	m_speedFactor = glm::vec2(4.0f, 4.0f);


// Back Button
		m_pBackButton = new Button("../Assets/textures/scene1.png", "backButton", BACK_BUTTON);
		m_pBackButton->getTransform()->position = glm::vec2(60.0f, 560.0f);
		m_pBackButton->addEventListener(CLICK, [&]()-> void
			{
				m_pBackButton->setActive(false);
				TheGame::Instance()->changeSceneState(PLAY_SCENE);
			});

		m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
			{
				m_pBackButton->setAlpha(128);
			});

		m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
			{
				m_pBackButton->setAlpha(255);
			});
		addChild(m_pBackButton);

		// Next Button
		m_pNextButton = new Button("../Assets/textures/Start.png", "startButton", START_BUTTON);
		m_pNextButton->getTransform()->position = glm::vec2(700.0f, 560.0f);
		m_pNextButton->addEventListener(CLICK, [&]()-> void
			{
				m_pNextButton->setActive(false);
				TheGame::Instance()->changeSceneState(START_SCENE);
			});

		m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
			{
				m_pNextButton->setAlpha(128);
			});

		m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
			{
				m_pNextButton->setAlpha(255);
			});

		addChild(m_pNextButton);
		const SDL_Color white = { 255, 255, 255, 255 };
		/* Instructions Label */
		m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Menu", "Consolas", 15, white);

		m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 570.0f);

		addChild(m_pInstructionsLabel);
		lblBallMass = new Label("Ball Mass: 1Kg", "Consolas", 20, white);
		lblBallMass->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 10.0f);
		addChild(lblBallMass);

		lblBrickMass = new Label("Brick Mass: 1Kg", "Consolas", 20, white);
		lblBrickMass->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 30.0f);
		addChild(lblBrickMass);

		lblWallFriction = new Label("Wall Friction: 0.9", "Consolas", 20, white);
		lblWallFriction->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 50.0f);
		addChild(lblWallFriction);
		lblBallVel = new Label("Ball Velocity: (0,0) m/s", "Consolas", 20, white);
		lblBallVel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 70.0f);
		addChild(lblBallVel);

		lblBrickVel = new Label("Brick Velocity: (0,0) m/s", "Consolas", 20, white);
		lblBrickVel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 90.0f);
		addChild(lblBrickVel);
}

void EndScene::reset()
{
	//m_pBall = NULL;

	m_pBall->m_WallFriction = 0.9f;
	m_pBrick->m_Mass = 20.0f;
	m_pBrick->getTransform()->position = glm::vec2(400, 500);
	m_pBall->m_Mass = 1.0f;
	m_pBall->getTransform()->position = glm::vec2(300, 300);
	m_pBall->isActive = false;
	m_pBall->Shape = 0;
	m_pBrick->isActive = false;
	m_pBrick->isHorizontal = 1;
}


void EndScene::StartSimulation() {
	
	m_pBall->reset();
	m_pBrick->isActive = true;
	m_pBall->isActive = true;
	m_pBall->changeShape();
	m_pBrick->changeHorizontal();
}
void EndScene::changeLabel() {
	std::string text = "Brick Mass: " + std::to_string(m_pBrick->m_Mass) + " Kg";
	lblBrickMass->setText(text);

	
		text = "Ball Mass: " + std::to_string(m_pBall->m_Mass) + " Kg";
		lblBallMass->setText(text);

		text = "Wall Friction: " + std::to_string(m_pBall->m_WallFriction);
		lblWallFriction->setText(text);
	
		text = "Brick Velocity: " + std::to_string(m_pBrick->getRigidBody()->velocity.x) +","+ std::to_string(m_pBrick->getRigidBody()->velocity.y) + " m/s";
		lblBrickVel->setText(text);


		text = "Ball Velocity: " + std::to_string(m_pBall->getRigidBody()->velocity.x) + "," + std::to_string(m_pBall->getRigidBody()->velocity.y) + " m/s";
		lblBallVel->setText(text);

	
}

void EndScene::m_updateUI()
{
	// Prepare Window Frame
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // use for debug purposes

	std::string windowString = "BOUNCING BALL";

	ImGui::Begin(&windowString[0], NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Separator();
	bool buttonPressed = ImGui::Button("Start Simulation");
	if (buttonPressed)
	{
		StartSimulation();
		//m_pLoot->doThrow();
	}

	ImGui::SameLine();
	if (ImGui::Button("Reset All"))
	{
		reset();
	}
	ImGui::Separator();
	if (ImGui::SliderFloat("Ball Mass (kg)", &m_pBall->m_Mass, 0.1f, 15, "%.1f"));
	if (ImGui::SliderFloat("Brick Mass (Kg)", &m_pBrick->m_Mass, 0.1f, 50, "%.1f"));
	if (ImGui::SliderFloat("Wall Friction", &m_pBall->m_WallFriction, 0.1f, 1, "%.1f"));
	//0 for circle, 1 for triangle, 2 for square, 3 for pentagon
	ImGui::Text("Ball: "); ImGui::SameLine();
	ImGui::RadioButton("Circle", &m_pBall->Shape, 0); ImGui::SameLine();
	ImGui::RadioButton("Triangle", &m_pBall->Shape, 1); ImGui::SameLine();
	ImGui::RadioButton("Square", &m_pBall->Shape, 2); ImGui::SameLine();
	ImGui::RadioButton("Pentagon", &m_pBall->Shape, 3);
	ImGui::Text("Brick: "); ImGui::SameLine();
	ImGui::RadioButton("Vertical", &m_pBrick->isHorizontal, 0); ImGui::SameLine();
	ImGui::RadioButton("Horizontal", &m_pBrick->isHorizontal, 1); 
	m_pBrick->changeHorizontal();
	changeLabel();
	

	// Main Window End
	ImGui::End();
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

//void EndScene::m_move()
//{
//
//
//	m_position = m_pBrick->getTransform()->position + m_velocity * m_speedFactor; // +m_acceleration;
//	m_pBrick->getTransform()->position = m_position;
//}
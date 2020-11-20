#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "Renderer.h"
#include <IMGUI\imgui.h>
#include <IMGUI_SDL\imgui_sdl.h>
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

	//m_pShip->draw();
	//m_pPlanet->draw();
	//m_pMine->draw();

	//for (auto ball : m_pBalls)
	//{
	if (m_pBall != NULL)
		m_pBall->draw();
//	}
//
	// ImGui Rendering section - DO NOT MOVE OR DELETE
	if (m_displayUI)
	{
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

		// debug collider shapes
	/*	Util::DrawLine(glm::vec2(0, 0), glm::vec2(0, Config::SCREEN_HEIGHT));
		Util::DrawLine(glm::vec2(0, 0), glm::vec2(Config::SCREEN_WIDTH, 0));
		Util::DrawLine(glm::vec2(0, Config::SCREEN_HEIGHT-1), glm::vec2(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT-1));
		Util::DrawLine(glm::vec2(Config::SCREEN_WIDTH-1, 0), glm::vec2(Config::SCREEN_WIDTH-1, Config::SCREEN_HEIGHT));*/
		if (m_pBall != NULL)
			Util::DrawRect(m_pBall->getTransform()->position - glm::vec2(m_pBall->getWidth() * 0.5f, m_pBall->getHeight() * 0.5f), m_pBall->getWidth(), m_pBall->getHeight());
		//Util::DrawRect(m_pPlanet->getPosition() - glm::vec2(m_pPlanet->getWidth() * 0.5f, m_pPlanet->getHeight() *0.5f), m_pPlanet->getWidth(), m_pPlanet->getHeight());
		//Util::DrawRect(m_pMine->getPosition() - glm::vec2(m_pMine->getWidth() * 0.5f, m_pMine->getHeight() *0.5f), m_pMine->getWidth(), m_pMine->getHeight());


		//Util::DrawCircle(m_pShip->getPosition(), std::max(m_pShip->getWidth() * 0.5, m_pShip->getHeight() * 0.5));
		//Util::DrawCircle(m_pPlanet->getPosition(), std::max(m_pPlanet->getWidth() * 0.5, m_pPlanet->getHeight() * 0.5));
		//Util::DrawCircle(m_pMine->getPosition(), std::max(m_pMine->getWidth() * 0.5, m_pMine->getHeight() * 0.5));
	}
}

void EndScene::update()
{
	m_move();
	m_pShip->update();
	//m_pPlanet->update();
	//m_pMine->update();
	//for (auto ball : m_pBalls)
	//{
	if (m_pBall != NULL)
		m_pBall->update();
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


	if (m_displayUI)
	{
		m_updateUI();
	}
}

void EndScene::clean()
{
	/*delete m_pStartLabel;
	delete m_pInstructionsLabel;*/

	delete m_pShip;

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
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		//m_pPlayer->getRigidBody()->velocity = glm::vec2(-m_pPlayer->SPEED, 0.0f);
		m_velocity = glm::vec2(-1.0f, m_velocity.y);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		//m_pPlayer->getRigidBody()->velocity = glm::vec2(m_pPlayer->SPEED, 0.0f);
		m_velocity = glm::vec2(1.0f, m_velocity.y);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		//m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, -m_pPlayer->SPEED);
		m_velocity = glm::vec2(m_velocity.x, -1.0f);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		//m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, m_pPlayer->SPEED);
		m_velocity = glm::vec2(m_velocity.x, 1.0f);
	}
	else {
		//m_pPlayer->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		//m_velocity = glm::vec2(0.0f, 0.0f);
		m_velocity = glm::vec2(1.0f, m_velocity.y);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
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

	m_position = glm::vec2(400.0f, 300.0f);
	m_pShip = new Brick();
	m_pShip->getTransform()->position = m_position;
	addChild(m_pShip);

	m_velocity = glm::vec2(0.0, 0.0); //glm::vec2(1.0f, m_velocity.y);
	m_speedFactor = glm::vec2(4.0f, 4.0f);





	// Instantiate a vector of Bullets
	//for (int i = 0; i < 5; ++i)
	//{
		
		//m_pBalls.push_back(ball);
	//}
// Back Button
		m_pBackButton = new Button("../Assets/textures/back.png", "backButton", BACK_BUTTON);
		m_pBackButton->getTransform()->position = glm::vec2(60.0f, 560.0f);
		m_pBackButton->addEventListener(CLICK, [&]()-> void
			{
				m_pBackButton->setActive(false);
				TheGame::Instance()->changeSceneState(START_SCENE);
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
		m_pNextButton = new Button("../Assets/textures/next.png", "nextButton", NEXT_BUTTON);
		m_pNextButton->getTransform()->position = glm::vec2(740.0f, 560.0f);
		m_pNextButton->addEventListener(CLICK, [&]()-> void
			{
				m_pNextButton->setActive(false);
				TheGame::Instance()->changeSceneState(END_SCENE);
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
}

void EndScene::reset()
{
	m_pBall = NULL;
}


void EndScene::StartSimulation() {
	m_pBall = new Ball();
	m_pBall->reset();
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

	

	

	// Main Window End
	ImGui::End();
}

void EndScene::m_move()
{


	m_position = m_pShip->getTransform()->position + m_velocity * m_speedFactor; // +m_acceleration;
	m_pShip->getTransform()->position = m_position;
}
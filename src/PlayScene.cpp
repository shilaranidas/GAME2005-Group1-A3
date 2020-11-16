#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include <string>

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("bg", Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2, 0, 255, true);

	
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}
void PlayScene::reset() {
	
	//m_pStormtrooper->getTransform()->position = glm::vec2(585.0f, fl);
	//m_pLoot->m_gravity = 9.8f;
	m_PPM = 1.0f;
	//m_pLoot->m_mass = 12.5f;
	//m_pLoot->m_PPM = 1.0f;
	//m_pLoot->m_Atime = 0.016667f;
	//m_pLoot->m_angle = 0.0f;
	//m_pLoot->m_velocity = 0.0f;
	//m_pLoot->m_velocityX = 0.0f;
	//m_pLoot->m_velocityY = 0.0f;
	//m_pLoot->m_acceleration = glm::vec2(0.0f, 0.0f);
	//m_pLoot->throwSpeed = glm::vec2(0.0f, 0.0f);
	//m_pLoot->buttonPressed = false;
	//m_pLoot->isGravityEnabled = false;
	
}
void PlayScene::start()
{
	//load background from texture.
	TextureManager::Instance()->load("../Assets/textures/bg.png", "bg");
	// Set GUI Title
	m_guiTitle = "Play Scene";
	//// Ball Sprite
	//m_pLoot = new Target();
	//addChild(m_pLoot);

	

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 450.0f);
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
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 450.0f);
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
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Menu", "Consolas",15,white);
	
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 490.0f);

	addChild(m_pInstructionsLabel);
	
	m_pMass = new Label("Mass: 12.8Kg", "Consolas", 20, white);
	m_pMass->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.9f, 10.0f);
	addChild(m_pMass);
	
	m_pVel = new Label("Velocity: 95m/s", "Consolas", 20, white);
	m_pVel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 30.0f);
	addChild(m_pVel);
	
	
	
	m_pForce = new Label("Force: 50N", "Consolas", 20, white);
	m_pForce->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.85f,110.0f);
	addChild(m_pForce);
	
	m_pAcce = new Label("Acceleration: 3m/s^2", "Consolas", 20, white);
	m_pAcce->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.8f, 150.0f);
	addChild(m_pAcce);
	reset();

}
void PlayScene::changeLabel() {
	//std::string text = "Velocity: " + std::to_string(m_pLoot->m_velocity) + " m/s";
	//m_pVel->setText(text);
	//text = "Mass: " + std::to_string(m_pLoot->m_mass) + " Kg";//Mass: 12.8Kg
	//m_pMass->setText(text);
	;
	//text = "distance: " + std::to_string(m_pStormtrooper->getTransform()->position.x- m_pBall->getTransform()->position.x) + " m";//Angle: 45degree

	//text = "Force: " + std::to_string(m_pLoot->m_pF) + " N";
	//m_pForce->setText(text);

	//std::cout << "labl" <<  m_pLoot->m_accelerationVal << std::endl;
	//text = "Acceleration: " + std::to_string(m_pLoot->m_accelerationVal);//Angle: 45degree
	//m_pAcce->setText(text);
}


void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Physics Simulation Control", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	ImGui::Separator();
	bool buttonPressed = ImGui::Button("Start Simulation");
	if (buttonPressed)
	{
		
		//m_pLoot->doThrow();
	}
	
	changeLabel();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"


#include "Renderer.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	//Sets the color for the background, values of RGB and alpha
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 127, 255, 212, 255);
	
	
	
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);


	m_pTeamLabel1 = new Label("Shila Rani Das-101141958", "Consolas", 25, black, glm::vec2(400.0f, 200.0f));
	m_pTeamLabel1->setParent(this);
	addChild(m_pTeamLabel1);
	
	// Scene1 Button
	m_pScene1Button = new Button("../Assets/textures/scene1.png","scene1Button",START_BUTTON, glm::vec2(250.0f, 400.0f),false);
	//m_pScene1Button.im
	//m_pScene1Button->getTransform()->position = glm::vec2(300.0f, 400.0f); 

	m_pScene1Button->addEventListener(CLICK, [&]()-> void
	{
		m_pScene1Button->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pScene1Button->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pScene1Button->setAlpha(128);
	});

	m_pScene1Button->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pScene1Button->setAlpha(255);
	});
	addChild(m_pScene1Button);


	// Scene2 Button
	//m_pScene2Button = new Button();
	m_pScene2Button = new Button("../Assets/textures/scene2.png", "scene1Button", START_BUTTON, glm::vec2(300.0f, 400.0f), false);
	m_pScene2Button->getTransform()->position = glm::vec2(500.0f, 400.0f);

	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(128);
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
		});
	addChild(m_pScene2Button);

	
}


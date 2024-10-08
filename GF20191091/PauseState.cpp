#include "Game.h"
#include "PauseState.h"
#include <iostream>
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string PauseState::s_pauseID = "PAUSE";
PauseState* PauseState::s_pInstance = NULL;


void PauseState::update()
{

	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

void PauseState::s_pauseToMain()
{
	PlayState::Instance() ->correct = 0;
    TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}


bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/resume.png", "resumebutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* button1 =
		new MenuButton(new LoaderParams(110, 200, 200, 80, "mainbutton"),
			s_pauseToMain);
	GameObject* button2 =
		new MenuButton(new LoaderParams(110, 300, 200, 80, "resumebutton"), s_resumePlay);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}
bool PauseState::onExit() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");

	std::cout << "Exit PauseState\n";
	return true;
}
void PauseState::s_resumePlay() { TheGame::Instance()->getStateMachine()->popState(); } //resum 누를 시 전에 있던 PlayState는 지속 되게
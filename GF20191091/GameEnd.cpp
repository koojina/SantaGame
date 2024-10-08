#include "Game.h"
#include "GameEnd.h"
#include"GameStateMachine.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include <iostream>
#include"AnimateGraphic.h"
const std::string GameEnd::s_gameOverID = "GAMEEND";
GameEnd* GameEnd::s_pInstance = NULL;

void GameEnd::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}
void GameEnd::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(
		PlayState::Instance());
}
void GameENd::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void GameEnd::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}
bool GameEnd::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext"), 2);
	GameObject* button1 = new MenuButton(
		new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(
		new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering GameOverState\n";
	return true;
}
bool GameEnd::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	std::cout << "exiting GameOverState\n";
	return true;
}
#include "Game.h"
#include "GameOverState.h"
#include"GameStateMachine.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include <iostream>
#include"AnimateGraphic.h"
#include"SDL_ttf.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";
GameOverState* GameOverState::s_pInstance = NULL;

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}
void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(
		PlayState::Instance());
}
void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
		
	}SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), Texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
bool GameOverState::onEnter()
{
	TTF_Init();
	char ns[10], n[10];
	if (!TheTextureManager::Instance()->load("assets/gameover.png", "gameovertext", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Gift.png", "Gift", TheGame::Instance()->getRenderer())) {
		return false;
	}
	font = TTF_OpenFont("assets/CookieRun_Black.ttf", 100);
	
	
	srcRect.x = 0;
    srcRect.y = 0;
	srcRect.w = destRect.w = 100;
	srcRect.h = destRect.h = 70;
	destRect.x =190;
	destRect.y = 146;
	//위치 변경
	if (font == NULL) {
		return false;
	}
	sprintf_s(n, "%d", PlayState::Instance()->correct);
	strcpy_s(ns, 10, "=");
	strcat_s(ns, sizeof(ns), n);
	NUMBER = TTF_RenderText_Solid(font, ns, Color);
	Texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), NUMBER);
	SDL_QueryTexture(Texture, NULL, NULL, &srcRect.w, &srcRect.h);
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(110, 100, 190, 30, "gameovertext"), 2);
	GameObject* Gift = new AnimatedGraphic(new LoaderParams(110, 146, 86, 51, "Gift"), 1);
	GameObject* button1 = new MenuButton(
		new LoaderParams(110, 200, 200, 80, "mainbutton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(
		new LoaderParams(110, 300, 200, 80, "restartbutton"), s_restartPlay); 

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(Gift);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering GameOverState\n";
	return true;
}
bool GameOverState::onExit()
{
	PlayState::Instance()->correct = 0;
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TTF_Quit();
	TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
	std::cout << "exiting GameOverState\n";
	return true;
}
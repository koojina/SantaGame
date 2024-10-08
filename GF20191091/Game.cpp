#include "Game.h"
#include"TextureManager.h"
#include"Player.h"
#include "Background.h"
#include"InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
Game* Game::s_pInstance = 0;
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
				
			}
			else { return false; }
		}
		else { return false; }
	}
	else { return false; }
	if ( !TheTextureManager::Instance()->load("assets/BG.png", "background", m_pRenderer)) //배경 설정
	{
		return false;
	}
	
	
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(MenuState::Instance());

	
	
	m_bRunning = true;
	return true;
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(PlayState::Instance());
	}
}
void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	SDL_Quit();
}
void Game::update()
{
	m_pGameStateMachine->update();
}
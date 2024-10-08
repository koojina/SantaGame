#pragma once
#include "SDL.h"
#include"SDL_image.h"
#include"Player.h"
#include"SDLGameObject.h"
#include "Enemy.h"
#include <vector>
class GameStateMachine;
class Game
{
	
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;
	
	Game() {}
	static Game* s_pInstance;

public:
	GameStateMachine* m_pGameStateMachine;
	GameStateMachine* getStateMachine()
	{
		return m_pGameStateMachine;
	}
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer()const { return m_pRenderer; }
	std::vector <GameObject*> m_gameObjects;
	bool init(const char*, int, int, int, int, int);
	void render();
	void update();
	bool running() { return m_bRunning; }
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }
};

typedef Game TheGame;
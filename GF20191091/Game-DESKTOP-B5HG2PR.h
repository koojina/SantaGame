#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include"TextureManager.h"
#include "Player.h"
class Game
{
public:
	Game() {}
	~Game() {}

	bool init(const char*, int, int, int, int, int);
	void render();
	void update();
	bool running() { return m_bRunning; }
	void handleEvents();
	void clean();
	GameObject m_go;
	Player m_player;

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	/*SDL_Texture* m_pTexture;
	원본 사각형
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
	SDL_Rect m_aaa;*/

	bool m_bRunning;
	int m_currentFrame;
	//TextureManager m_textureManager;

};

//#endif/*defined(__Game__)*/
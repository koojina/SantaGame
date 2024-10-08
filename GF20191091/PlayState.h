#pragma once
#include"GameState.h"
#include"SDL_mixer.h"
#include"SDLGameObject.h"
class PlayState : public GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
    static void t();
	static void f();
	virtual std::string getStateID()const { return s_playID; }
	static PlayState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	int correct=0;
private:
	PlayState() {};
	static const std::string s_playID;
	Mix_Music* music;
	static PlayState* s_pInstance;
	int h1 = 0;
	int h2 = 0;
	
};
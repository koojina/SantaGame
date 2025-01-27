#pragma once
#include "GameState.h"
class GameObject;
class GameEnd :public GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }
	static GameOverState* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}
private:
	static void s_gameOverToMain();
	static void s_restartPlay();
	static const std::string s_gameOverID;

	GameOverState() {}
	static GameOverState* s_pInstance;
};
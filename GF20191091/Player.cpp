#include"Player.h"
#include"SDLGameObject.h"
#include"InputHandler.h"
Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Player::draw() {
	SDLGameObject::draw();
}
void Player::update() {
	m_currentFrame = int(((SDL_GetTicks() / 100) % 2)); //산타 프레임 두 개
	m_velocity.setX(0.5); //속도
	SDLGameObject::update();
}
void Player::clean() {}

#include "Enemy.h"
#include"InputHandler.h"
#include"SDLGameObject.h"
#include<vector>
Enemy::Enemy(const LoaderParams* pParams) :SDLGameObject(pParams) {}
void Enemy::draw() {
	SDLGameObject::draw();
}
void Enemy::update() {
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	
	SDLGameObject::update();
}
void Enemy::clean() {}
void Enemy::handlerInput() {
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*vec - m_position) / 100;
}
//배경을 기존의 Player와 같은 기능을 하도록 설정
#include"Background.h"
#include"SDLGameObject.h"
Background::Background(const LoaderParams* pParams) :SDLGameObject(pParams) {}

void Background::draw() {
	SDLGameObject::draw();
}
void Background::update() {
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));//움직이는 것 없게 설정
}
void Background::clean() {}
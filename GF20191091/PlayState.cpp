#include "PlayState.h"
#include "GameObject.h"
#include <iostream>
#include"Background.h"
#include"Game.h"
#include"TextureManager.h"
#include <time.h>
#include "MenuButton.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameStateMachine.h"
#include "GameOverState.h"
#include "PlayState.h"
const std::string PlayState::s_playID = "PLAY";
PlayState* PlayState::s_pInstance = NULL;
const int x[48] = { 47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302,47,98,149,200,251,302 }; //x위치
const int y[48] = { 49,49,49,49,49,49,122,122,122,122,122,122,195,195,195,195,195,195,268,268,268,268,268,268,341,341,341,341,341,341,414,414,414,414,414,414,487,487,487,487,487,487,560,560,560,560,560,560}; //y위치

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
	if (m_gameObjects.size()!=0&&h1!=0&&h2!=0&&checkCollision(
		dynamic_cast <SDLGameObject*>(m_gameObjects[h1]),
		dynamic_cast<SDLGameObject*>(m_gameObjects[h2]))) {
		TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance());
	} //산타와 선물이 닿으면 GameOver
}
void PlayState::render()
{
	
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}
bool PlayState::onEnter()
{
	
	
	m_gameObjects.push_back(new Background(new LoaderParams(0, 0, 400, 711, "background")));//Play 누를 시 뒷배경 생성
	
		if (!TheTextureManager::Instance()->load("assets/Santa.png", "Santa",
			TheGame::Instance()->getRenderer())) {
			return false; //산타 오브젝트
		}
		if (!TheTextureManager::Instance()->load("assets/Gift.png", "Gift",
			TheGame::Instance()->getRenderer())) {
			return false; //선물 오브젝트
		}
		// 오브젝트 위치
		GameObject* player = new Player(
			new LoaderParams(0, 0, 127.5, 48, "Santa"));
		GameObject* enemy = new Enemy(
			new LoaderParams(320, 0, 107, 54, "Gift"));
		m_gameObjects.push_back(player);
		h1 = m_gameObjects.size() - 1; //player의 vector 배열 이용 (마지막에 push.back 한 것을 찾으려고 -1)
		m_gameObjects.push_back(enemy);
		h2 = m_gameObjects.size() - 1; //player의 vector 배열 이용 (위와 동일)
	
	if (!TheTextureManager::Instance()->load("assets/card 1.png", "Card 1",
		TheGame::Instance()->getRenderer())||!TheTextureManager::Instance()->load("assets/card 1_2.png", "Card 2", 
			TheGame::Instance()->getRenderer())) {
		return false;
	}//카드 로드 못할 경우 반환값 false
	//SDL Music
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096); //Music 라이브러리
	music = Mix_LoadMUS("assets/We Wish You A Merry Christmas.mp3"); //mp3 파일 
	Mix_VolumeMusic(60); //볼륨
	Mix_PlayMusic(music, -1); //무한반복
	
	int r = 0; //초기화
	srand((unsigned int)time(NULL)); // 랜덤
	r = rand() % 48; //전체 카드 개수
	m_gameObjects.push_back(new MenuButton(new LoaderParams(x[r], y[r], 51, 73, "Card 2"),t)); //빨강코 랜덤 위치 생성
	for (int i = 0; i < 48; i++) {
		if (i == r)
			continue; //중복방지
		m_gameObjects.push_back(new MenuButton(new LoaderParams(x[i], y[i], 51, 73, "Card 1"), f)); //주황코 빨강코 위치 제외한 나머지 위치에 생성
	} //배열 값으로 랜덤 생성
	std::cout << "entering PlayState\n";
	return true;
}
bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("Card 1");
	TheTextureManager::Instance()
		->clearFromTextureMap("Card 2");
	//Music 정지
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	std::cout << "exiting PlayState\n";
	return true;
}
void PlayState::t() //루돌프를 찾았을 경우
{
	PlayState::Instance()->correct++; //루돌프 찾은 개수
	std::cout << "Red button clicked\n";
	std::cout << PlayState::Instance()->correct<<std::endl; //찾은 개수 출력
	TheGame::Instance()->getStateMachine()->changeState(
			PlayState::Instance()); //다시 실행
}
	
		
	


void PlayState::f() //그냥 사슴 찾았을 경우
{
	std::cout << "Org button clicked\n"; //주황 코
	TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance()); //바로 GameOver
	
}
bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB)return false;
	if (topA >= bottomB)return false;
	if (rightA <= leftB)return false;
	if (leftA >= rightB)return false;

	return true;
}
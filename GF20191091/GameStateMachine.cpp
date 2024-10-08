#include "GameStateMachine.h"
#include "PauseState.h"
#include"PlayState.h"
#include "MenuState.h"
void GameStateMachine::popState()
{
	if (m_currentState != PauseState::Instance()) { //현재 PauseState가 아닐 때 전 State로 변경
		
		changeState(m_prevState);
	}
	else { //현재가 PauseState가 아닐 때 (resum) 
		m_currentState->onExit(); //현재를 나가고
		SDL_Delay(200); //버튼 같이 눌리는 것 방지
		m_currentState = m_prevState; //전 State를 현재 State로

	}
}
void GameStateMachine::changeState(GameState* pState)
{
	if (pState != NULL )
	{
		if (m_currentState != NULL) {
			
				m_prevState = m_currentState;
         if (pState != PauseState::Instance()) //바꾸려고 하는 State가 PauseState가 아닐 때만 실행 (resum 경우 생각)
				m_currentState->onExit();
			
		}	
	   m_currentState = pState;
	   SDL_Delay(150); // 버튼 같이 눌림 방지 
	   m_currentState->onEnter();
		

	}
}
void GameStateMachine::update()
{
	if (m_currentState != NULL)
		m_currentState->update();
}
void GameStateMachine::render() {
	if (m_currentState != NULL)
		m_currentState->render();
}
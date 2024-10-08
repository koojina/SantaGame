#pragma once
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
class SDLGameObject : public GameObject {
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual ~SDLGameObject() {}
	Vector2D m_velocity;
    Vector2D m_acceleration;
	Vector2D m_position;
	Vector2D getPosition() const { return m_position; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int m_numFrames = 2; //버그 수정 (GameOver Text 안 보이는 버그)
protected:
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;
};


#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Agent.h"

class Player : public Agent
{
public:
	Player();
	Player(float _posX, float _posY);
	~Player();

	void Update(float _deltaTime);
	void Draw(aie::Renderer2D* _renderer);

private:
	aie::Texture* m_Texture;

};


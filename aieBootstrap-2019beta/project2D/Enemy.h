#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Pathfinder.h"
#include "Agent.h"

class Enemy : public Agent
{
public:
	Enemy();
	Enemy(float _posX, float _posY);
	~Enemy();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	aie::Texture* m_Texture;

};


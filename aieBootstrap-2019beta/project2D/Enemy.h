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
	Enemy(float _posX, float _posY, Agent* _target);
	~Enemy();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	Agent* m_Target;

	aie::Texture* m_BodyTexture;
	aie::Texture* m_GunTexture;

};


#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Agent.h"

class Pathfinder;

class Enemy : public Agent
{
public:
	Enemy();
	Enemy(float _posX, float _posY, Agent* _target, Pathfinder* _pathfinder);
	~Enemy();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	Pathfinder* m_Pathfinder = nullptr;
	std::vector<Vector2> m_Path;
	Agent* m_Target = nullptr;

	aie::Texture* m_BodyTexture;
	aie::Texture* m_GunTexture;
	aie::Texture* m_ExclamationTexture;

	float m_AttackRange = 400;
	float m_TargetDistance = 0;
	bool m_Attacking = false;
};


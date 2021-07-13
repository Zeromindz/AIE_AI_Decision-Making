#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Agent.h"

class Pathfinder;

class Enemy : public Agent
{
public:
	Enemy(Agent* _target);
	~Enemy();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	Pathfinder* m_Pathfinder = nullptr;
	std::vector<Vector2> m_Path;
	Agent* m_Target = nullptr;

	aie::Texture* m_BodyTexture = nullptr;
	aie::Texture* m_GunTexture = nullptr;
	aie::Texture* m_ExclamationTexture = nullptr;

	float m_AttackRange = 400;
	float m_TargetDistance = 0;
	bool m_Attacking = false;
};


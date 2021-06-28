#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	m_texture = new aie::Texture("./textures/ship.png");
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Speed = 5;

}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{

}


void Enemy::Move(std::vector<Vector2> _path, float deltaTime)
{
	// TODO Pathfinding
	for (int i = 0; i < _path.size(); i++)
	{


	}

}

void Enemy::Draw(aie::Renderer2D* renderer)
{
	// Draw the enemies sprite.
	renderer->SetRenderColour(1.0f, 0.0f, 0.0f);
	renderer->DrawSprite(m_texture, m_Pos.x, m_Pos.y);

	renderer->SetRenderColour(1.0f, 1.0f, 1.0f);

}




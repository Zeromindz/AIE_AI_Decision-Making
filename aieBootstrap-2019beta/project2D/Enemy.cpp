#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	// Load enemy sprite
	m_Texture = new aie::Texture("./textures/ship.png");

	// default enemy position to 0
	SetPostition({0, 0});
}

Enemy::Enemy(float _posX, float _posY)
{
	m_Texture = new aie::Texture("./textures/ship.png");

	SetPostition({_posX, _posY});
}

Enemy::~Enemy()
{
	// Delete the enemie's sprite.
	delete m_Texture;
	m_Texture = nullptr;
}

void Enemy::Update(float _deltaTime)
{
	Agent::Update(_deltaTime);
}


void Enemy::Draw(aie::Renderer2D* _renderer)
{

	// Calculate normalized movement vector
	Vector2 moveDir = GetVelocity().Normalize();
	// Calculate sprite rotation angle
	float angle = atan2(moveDir.y, moveDir.x) - (3.141592653589793 / 2);

	// Draw the enemies sprite.
	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50, 50, 50, angle);
	_renderer->SetRenderColour(1.0f, 0.0f, 0.0f);
	_renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y, 0, 0, angle);
	
	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);

}




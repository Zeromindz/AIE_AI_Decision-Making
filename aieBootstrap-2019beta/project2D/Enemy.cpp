#include "Enemy.h"
#include "Input.h"
#include "PathFinder.h"

Enemy::Enemy(Agent* _target)
{
	m_Target = _target;

	// Load enemy sprite
	m_BodyTexture = new aie::Texture("Assets/textures/tankBeige.png");
	m_GunTexture = new aie::Texture("Assets/textures/barrelBeige.png");
	m_ExclamationTexture = new aie::Texture("Assets/textures/exclamation_mark_001.png");

}

Enemy::~Enemy()
{
	// Delete the enemy sprite.
	delete m_BodyTexture;
	m_BodyTexture = nullptr;
}

void Enemy::Update(float _deltaTime)
{
	Agent::Update(_deltaTime);
	
	m_TargetDistance = (m_Target->GetPosition() - GetPosition()).Magnitude();
	
	m_Attacking = (m_TargetDistance < m_AttackRange);
}

void Enemy::Draw(aie::Renderer2D* _renderer)
{
	Agent::Draw(_renderer);

	Vector2 m_StartPos = GetPosition();
	Vector2 m_EndPos = m_Target->GetPosition();

	// Calculate normalized movement vector
	Vector2 moveDir = GetVelocity().Normalize();
	// Calculate sprite rotation angle
	float angle = atan2(moveDir.y, moveDir.x) - (3.141592653589793 / 2);

	Vector2 aimDir = m_Target->GetPosition() - GetPosition();
	float aimAngle = atan2(aimDir.y, aimDir.x) - (3.141592653589793 / 2);

	// Draw the enemy's shadow.
	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_BodyTexture, GetPosition().x + 5, GetPosition().y - 5, 0, 0, angle);
	// Draw the enemy's body sprite.
	_renderer->SetRenderColour(200.0f / 255, 50.0f / 255, 50.0f / 255);
	_renderer->DrawSprite(m_BodyTexture, GetPosition().x, GetPosition().y, 0, 0, angle);
	// Draw the enemy's gun sprite.
	_renderer->SetRenderColour(140.0f / 255, 30.0f / 255, 30.0f / 255);
	_renderer->DrawSprite(m_GunTexture, GetPosition().x, GetPosition().y, 0, 0, aimAngle);

	if (m_Attacking)
	{
		_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
		_renderer->DrawSprite(m_ExclamationTexture, GetPosition().x, GetPosition().y + 60, 20, 80);
	}
	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}




#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	// Load enemy sprite
	m_BodyTexture = new aie::Texture("Assets/textures/tankBeige.png");
	m_GunTexture = new aie::Texture("Assets/textures/barrelBeige.png");

	// default enemy position to 0
	SetPostition({0, 0});
}

Enemy::Enemy(float _posX, float _posY, Agent* _target)
{
	m_BodyTexture = new aie::Texture("Assets/textures/tankBeige.png");
	m_GunTexture = new aie::Texture("Assets/textures/barrelBeige.png");

	SetPostition({_posX, _posY});

	m_Target = _target;
}
Enemy::~Enemy()
{
	//$(SolutionDir)temp\$(ProjectName)\$(Platform)\$(Configuration)\

	// Delete the enemie's sprite.
	delete m_BodyTexture;
	m_BodyTexture = nullptr;
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

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}




#include "Projectile.h"

Projectile::Projectile()
{
	// Load the projectile's sprite.
	m_Texture = new aie::Texture("Assets/textures/rock_small.png");

	
}

Projectile::Projectile(float _posX, float _posY)
{
	m_Texture = new aie::Texture("Assets/textures/rock_small.png");
	SetPostition({ _posX, _posY });

}

Projectile::~Projectile()
{
}

void Projectile::Update(float _deltaTime)
{
	Agent::Update(_deltaTime);
}

void Projectile::Draw(aie::Renderer2D* _renderer)
{
	// Calculate normalized movement vector
	Vector2 moveDir = GetVelocity().Normalize();
	// Calculate sprite rotation angle
	float angle = atan2(moveDir.y, moveDir.x) - (3.141592653589793 / 2);

	// Draw the projectile's shadow.
	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50, 20, 20, angle);
	// Draw the projectile's sprite.
	_renderer->SetRenderColour(300.0f / 255, 50.0f / 255, 50.0f / 255);
	_renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y, 0, 0, angle);

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}

#include <math.h>
#include "Player.h"
#include "Input.h"

Player::Player()
{
	// Load the player's sprite.
	m_Texture = new aie::Texture("Assets/textures/ship.png");

	// Set the player's position.
	SetPostition({ 600, 400 });
}

Player::Player(float _posX, float _posY)
{
	m_Texture = new aie::Texture("Assets/textures/ship.png");

	SetPostition({ _posX, _posY });
}

Player::~Player()
{
	// Delete the player's sprite.
	delete m_Texture;
	m_Texture = nullptr;
}

void Player::Update(float _deltaTime)
{
	Agent::Update(_deltaTime);
}

void Player::Draw(aie::Renderer2D* _renderer)
{
	// Calculate normalized movement vector
	Vector2 moveDir = GetVelocity().Normalize();
	// Calculate sprite rotation angle
	float angle = atan2(moveDir.y, moveDir.x) - (3.141592653589793 / 2);

	// Draw the player's shadow.
	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50, 50, 50, angle);
	// Draw the player's sprite.
	_renderer->SetRenderColour(3.0f / 255, 71.0f / 255, 188.0f / 255);
	_renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y, 0, 0, angle);

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}


#include "Player.h"
#include "Input.h"

Player::Player()
{
	// Load the player's sprite.
	m_Texture = new aie::Texture("./textures/ship.png");

	// Set the player's position.
	SetPostition({ 600, 400 });
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
	// Draw the player's shadow and sprite.
	_renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	_renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50);
	_renderer->SetRenderColour(0.0f, 0.0f, 1.0f);
	_renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y);

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
}


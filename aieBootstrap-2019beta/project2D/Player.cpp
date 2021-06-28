#include "Player.h"
#include "Input.h"

Player::Player()
{
	// Load the player's sprite.
	m_Texture = new aie::Texture("./textures/ship.png");

	// Set the player's position.
	m_Pos.x = 600;
	m_Pos.y = 400;
}

Player::~Player()
{
	// Delete the player's sprite.
	delete m_Texture;
	m_Texture = nullptr;
}

void Player::Update(float deltaTime)
{
	// Update input for the player.
	aie::Input* input = aie::Input::GetInstance();
	if (input->IsKeyDown(aie::INPUT_KEY_LEFT))
	{
		m_Pos.x -= 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_RIGHT))
	{
		m_Pos.x += 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_UP))
	{
		m_Pos.y += 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_DOWN))
	{
		m_Pos.y -= 500.0f * deltaTime;
	}
}

void Player::Draw(aie::Renderer2D* renderer)
{
	// Draw the player's shadow and sprite.
	renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	renderer->DrawSprite(m_Texture, m_Pos.x + 30, m_Pos.y - 50);
	renderer->SetRenderColour(0.0f, 0.0f, 1.0f);
	renderer->DrawSprite(m_Texture, m_Pos.x, m_Pos.y);

}

Vector2 Player::GetPos()
{
	return m_Pos;
}

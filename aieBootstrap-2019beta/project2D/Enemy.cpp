#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	// Load enemy sprite
	m_Texture = new aie::Texture("./textures/ship.png");

	// Set enemie's position
	SetPostition({0, 0});
}

Enemy::~Enemy()
{
	// Delete the enemie's sprite.
	delete m_Texture;
	m_Texture = nullptr;
}

void Enemy::Update(float deltaTime)
{

}


void Enemy::Draw(aie::Renderer2D* renderer)
{
	// Draw the enemies sprite.
	renderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	renderer->DrawSprite(m_Texture, GetPosition().x + 30, GetPosition().y - 50);
	renderer->SetRenderColour(1.0f, 0.0f, 0.0f);
	renderer->DrawSprite(m_Texture, GetPosition().x, GetPosition().y);
	
	renderer->SetRenderColour(1.0f, 1.0f, 1.0f);

}




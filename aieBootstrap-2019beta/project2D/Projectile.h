#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Agent.h"

class Projectile : public Agent
{
public:
	Projectile();
	Projectile(float _posX, float _posY);
	~Projectile();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	aie::Texture* m_Texture;

};


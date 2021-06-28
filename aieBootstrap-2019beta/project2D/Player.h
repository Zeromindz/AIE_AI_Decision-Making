#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"

class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

	Vector2 GetPos();

private:
	aie::Texture* m_Texture;

	Vector2 m_Pos;
};


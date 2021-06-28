#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Pathfinder.h"
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update(float deltaTime);
	void Move(std::vector<Vector2> _path, float _deltaTime);
	void Draw(aie::Renderer2D* renderer);

	aie::Texture* m_texture;
	Vector2 m_Pos;
	float m_Speed;

private:

};


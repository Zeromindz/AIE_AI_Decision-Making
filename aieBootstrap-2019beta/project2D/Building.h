#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"

class Building
{
public:
	Building();
	Building(float _posX, float _posY);
	~Building() {}

	Vector2 GetPosition() { return { m_PosX, m_PosY }; }
	bool IsAlive() { return m_Alive; }
	void SetAlive(bool _alive) { m_Alive = _alive; }
	void Draw(aie::Renderer2D* _renderer);

private:
	float m_PosX = 0;
	float m_PosY = 0;

	bool m_Alive = false;
	aie::Texture* m_Texture;
};


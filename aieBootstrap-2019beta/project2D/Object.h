#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

class Object
{
public:
	Object() {}
	Object(Vector2 _pos) { m_Position = _pos; }
	~Object() {}

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer);

	Vector2 GetPosition() { return m_Position; }
	void SetPosition(Vector2 _pos) { m_Position = _pos; }

private:
	Vector2 m_Position = { 0, 0 };
};


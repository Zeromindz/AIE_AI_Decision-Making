#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Pathfinder.h"
#include "Player.h"
#include "Enemy.h"
#include "Agent.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"

class Player;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D* m_2dRenderer;

	Pathfinder* m_Pathfinder;

	// Example textures.
	aie::Font* m_font;

	Player* m_Player;
	Enemy* m_Enemy;

	KeyboardBehaviour* m_KeyboardBehaviour;
	SeekBehaviour* m_SeekBehaviour;

	Vector2 m_StartPos;
	Vector2 m_EndPos;
	std::vector<Vector2> m_Path;
};
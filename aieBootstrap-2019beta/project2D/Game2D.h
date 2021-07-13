#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Input.h"
#include "Vector2.h"

class Pathfinder;
class Player;
class Enemy;
class Projectile;
class Building;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	void Initialize();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	Pathfinder* m_Pathfinder;
	Player* m_Player;
	std::vector<Enemy*> m_EnemyList;
	Projectile* m_Projectile;
	Enemy* m_WanderingEnemy;

	Building* m_Building;

	std::vector<Vector2> m_Path;

	float m_Dist = 0;
	int m_EnemyCount = 3;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_Font;
	aie::Input* m_Input;
};
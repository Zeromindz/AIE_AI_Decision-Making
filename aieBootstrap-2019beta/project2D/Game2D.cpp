
#include "Application.h"
#include "Game2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Pathfinder.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FollowBehaviour.h"
#include "WanderBehaviour.h"
#include "PathFollowBehaviour.h"
#include "Building.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_Input = aie::Input::GetInstance();
	m_2dRenderer = new aie::Renderer2D();
	m_Font = new aie::Font("Assets/font/consolas_bold.ttf", 24);

	// Create pathfinder
	m_Pathfinder = new Pathfinder();

	// Create agents.
	m_Player = new Player();
	m_EnemyCount = 3;
	for (int i = 0; i < m_EnemyCount; i++)
	{
		m_EnemyList.push_back(new Enemy(i * 200, i * 200, m_Player, m_Pathfinder));
	}
	m_Projectile = new Projectile();

	// Create building
	m_Building = new Building(400, 400);

	//Initialize position vectors to 0 for path visualization
	m_StartPos = { 0, 0 };
	m_EndPos = { 0, 0 };

	// Add behaviours
	m_Player->AddBehaviour(new KeyboardBehaviour());
	for (int i = 0; i < m_EnemyCount; i++)
	{
		m_EnemyList[i]->AddBehaviour(new PathFollowBehaviour(m_Pathfinder, m_Player));
	}
	
	m_Projectile->AddBehaviour(new FollowBehaviour(m_Player));
}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;

	for each (Enemy * e in m_EnemyList)
	{
		delete e;
	}

	// Delete the textures.
	delete m_Font;

	// Delete the renderer and pathfinder.
	delete m_2dRenderer;
	delete m_Pathfinder;

}

void Game2D::Update(float deltaTime)
{
	// Update camera position
	m_2dRenderer->SetCameraPos(m_Player->GetPosition().x - 600, m_Player->GetPosition().y - 300);
	//===================================================================/
	// Update agents.
	//_________________________________________________________________/
	m_Player->Update(deltaTime);
	for (int i = 0; i < m_EnemyCount; i++)
	{
		m_EnemyList[i]->Update(deltaTime);
	}
	m_Projectile->Update(deltaTime);
	

	// Get dist from enemy to player
	m_Dist = (m_Player->GetPosition() - m_EnemyList[0]->GetPosition()).Magnitude();

	//====================================================================/
	// Create and remove walls
	//_________________________________________________________________/
	if (m_Input->IsMouseButtonDown(0))
	{
		float x = m_Input->GetMouseX();
		float y = m_Input->GetMouseY();

		GraphNode* target = m_Pathfinder->GetNodeByPos({ x + m_Player->GetPosition().x - 600, y + m_Player->GetPosition().y - 300 });
		if (target)
		{
			target->m_Blocked = true;
		}
	}
	if (m_Input->IsMouseButtonDown(1))
	{
		float x = m_Input->GetMouseX();
		float y = m_Input->GetMouseY();

		GraphNode* target = m_Pathfinder->GetNodeByPos({ x + m_Player->GetPosition().x - 600, y + m_Player->GetPosition().y - 300 });
		if (target)
		{
			target->m_Blocked = false;
		}
	}
	// Create large walls while boosting
	if (m_Input->IsKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	{
		GraphNode* target = m_Pathfinder->GetNodeByPos({ m_Player->GetPosition().x,m_Player->GetPosition().y });

		if (target)
		{
			target->m_Blocked = true;
			for (int i = 0; i < 8; i++)
			{
				if (target->m_Neighbors[i] != nullptr)
				{
					target->m_Neighbors[i]->m_Blocked = true;

				}
			}
		}
	}

	// Exit the application if escape is pressed.
	if (m_Input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();
	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();
	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	//Draw grid
	m_Pathfinder->Render(m_2dRenderer);
	
	// Pathfinding
	
	m_StartPos = m_EnemyList[0]->GetPosition();
	m_EndPos = m_Player->GetPosition();
	
	GraphNode* startNode = m_Pathfinder->GetNodeByPos(m_StartPos);
	GraphNode* endNode = m_Pathfinder->GetNodeByPos(m_EndPos);
	
	if (startNode && endNode)
	{
		if (!startNode->m_Blocked && !endNode->m_Blocked)
		{
			m_Pathfinder->AStarPath(m_StartPos, m_EndPos, m_Path);
			// Draw Path
			m_2dRenderer->SetRenderColour(1.0f, 0.0f, 0.0f);
			for (int i = 0; i < m_Path.size() - 1; ++i)
			{
				if (i < m_Path.size())
				{
					m_2dRenderer->DrawLine(m_Path[i].x, m_Path[i].y, m_Path[i + 1].x, m_Path[i + 1].y, 6.0f);
	
				}
			}
		}
	}
	
	// Reset colour to default
	m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f);
	
	// Draw agents
	m_Player->Draw(m_2dRenderer);
	for (int i = 0; i < m_EnemyCount; i++)
	{
		m_EnemyList[i]->Draw(m_2dRenderer);
	}
	m_Projectile->Draw(m_2dRenderer);

	// Draw buildings
	m_Building->Draw(m_2dRenderer);
	
	//=============================================================/
	// Debugging
	//___________________________________________________________/
	
	// Text showing the distance from enemy to player
	char dist[32];
	sprintf_s(dist, 32, "DIST: %i", (int)m_Dist);
	m_2dRenderer->DrawText2D(m_Font, dist, m_EnemyList[0]->GetPosition().x, m_EnemyList[0]->GetPosition().y);

	// Draw a line between player and enemy
	m_2dRenderer->DrawLine(m_Player->GetPosition().x, m_Player->GetPosition().y, m_EnemyList[0]->GetPosition().x, m_EnemyList[0]->GetPosition().y, 2.0f);

	// Performance text
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_Font, fps, m_Player->GetPosition().x - 400, m_Player->GetPosition().y + 350);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}



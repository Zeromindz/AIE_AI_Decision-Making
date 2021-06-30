
#include "Application.h"
#include "Game2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_Input = aie::Input::GetInstance();
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 24);

	// Create a player, enemy and pathfinder.
	m_Player = new Player();
	m_Enemy = new Enemy(500, 500, m_Player);
	m_Pathfinder = new Pathfinder();

	m_Projectile = new Projectile();

	
	//Initialize position vectors to 0 for path visualization
	m_StartPos = { 0, 0 };
	m_EndPos = { 0, 0 };

	// Add behaviours
	m_Player->AddBehaviour(new KeyboardBehaviour());
	m_Enemy->AddBehaviour(new WanderBehaviour());

	m_Projectile->AddBehaviour(new FollowBehaviour(m_Player));

}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;
	delete m_Enemy;

	// Delete the textures.
	delete m_font;

	// Delete the renderer and pathfinder.
	delete m_2dRenderer;
	delete m_Pathfinder;

}

void Game2D::Update(float deltaTime)
{
	//TODO follow player with camera
	m_2dRenderer->SetCameraPos(m_Player->GetPosition().x - 600, m_Player->GetPosition().y - 300);

	// Update the player.
	m_Player->Update(deltaTime);
	m_Enemy->Update(deltaTime);
	m_Projectile->Update(deltaTime);

	// Create and remove walls
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
	// Drop walls while boosting
	//if (m_Input->IsKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	//{
	//	GraphNode* target = m_Pathfinder->GetNodeByPos({ m_Player->GetPosition().x,m_Player->GetPosition().y});
	//
	//	if (target)
	//	{
	//		target->m_Blocked = true;
	//	}
	//}
	
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

	// Draw grid
	m_Pathfinder->Render(m_2dRenderer);

	// Pathfinding

	m_StartPos = m_Enemy->GetPosition();
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

	m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f);

	// Draw Player
	m_Player->Draw(m_2dRenderer);
	// Draw Enemy
	m_Enemy->Draw(m_2dRenderer);
	m_Projectile->Draw(m_2dRenderer);
	// Draw following object
	//m_2dRenderer->SetRenderColour(0.0f, 0.0f, 0.0f, 0.7f);
	//m_2dRenderer->DrawCircle(m_FollowAgent->GetPosition().x + 30, m_FollowAgent->GetPosition().y - 50, 10.0f);
	//m_2dRenderer->SetRenderColour(0.0f, 0.0f, 0.0f);
	//m_2dRenderer->DrawCircle(m_FollowAgent->GetPosition().x, m_FollowAgent->GetPosition().y, 14.0f);
	//m_2dRenderer->SetRenderColour(1.0f, 0.0f, 0.0f);
	//m_2dRenderer->DrawCircle(m_FollowAgent->GetPosition().x, m_FollowAgent->GetPosition().y, 10.0f);
	//m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f);
	
	// Draw text
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, m_Player->GetPosition().x - 550, m_Player->GetPosition().y - 250);
	m_2dRenderer->DrawText2D(m_font, "WASD to move.", 15.0f, windowHeight - 64.0f);


	// Draw a thin line.
	//m_2dRenderer->DrawLine(150.0f, 400.0f, 250.0f, 500.0f, 2.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}



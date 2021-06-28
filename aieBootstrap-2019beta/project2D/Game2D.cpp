#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 24);

	// Create a player, enemy and pathfinder.
	m_Player = new Player();
	m_Enemy = new Enemy();
	m_Pathfinder = new Pathfinder();
}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;
	m_Player = nullptr;
	delete m_Enemy;
	m_Enemy = nullptr;

	// Deleted the textures.
	delete m_font;


	// Delete the renderer and pathfinder.
	delete m_2dRenderer;
	delete m_Pathfinder;

}

void Game2D::Update(float deltaTime)
{
	// Input
	aie::Input* input = aie::Input::GetInstance();

	//TODO follow player with camera
	m_2dRenderer->SetCameraPos(m_Player->GetPos().x - 600, m_Player->GetPos().y - 300);
	//aie::Input* input = aie::Input::GetInstance();
	//if (input->IsKeyDown(aie::INPUT_KEY_W))
	//	m_Pos.y += 500.0f * deltaTime;
	//
	//if (input->IsKeyDown(aie::INPUT_KEY_S))
	//	m_Pos.y -= 500.0f * deltaTime;
	//
	//if (input->IsKeyDown(aie::INPUT_KEY_A))
	//	m_Pos.x -= 500.0f * deltaTime;
	//
	//if (input->IsKeyDown(aie::INPUT_KEY_D))
	//	m_Pos.x += 500.0f * deltaTime;


	// Update the player.
	m_Player->Update(deltaTime);
	m_Enemy->Update(deltaTime);
	m_Enemy->Move(m_Path, deltaTime);

	// Create and remove walls
	if (input->IsMouseButtonDown(0))
	{
		float x = input->GetMouseX();
		float y = input->GetMouseY();

		GraphNode* target = m_Pathfinder->GetNodeByPos({ x, y });
		if (target)
		{
			target->m_Blocked = true;
		}
	}
	if (input->IsMouseButtonDown(1))
	{
		float x = input->GetMouseX();
		float y = input->GetMouseY();

		GraphNode* target = m_Pathfinder->GetNodeByPos({ x, y });
		if (target)
		{
			target->m_Blocked = false;
		}
	}


	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
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

	m_StartPos = m_Player->GetPos();
	m_EndPos = m_Enemy->m_Pos;

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

	// Draw text
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);
	m_2dRenderer->DrawText2D(m_font, "Arrow keys to move.", 15.0f, windowHeight - 64.0f);
	m_2dRenderer->DrawText2D(m_font, "WASD to move camera.", 15.0f, windowHeight - 96.0f);
	m_2dRenderer->DrawText2D(m_font, "Press ESC to quit!", 15.0f, windowHeight - 128.0f);

	// Draw a thin line.
	//m_2dRenderer->DrawLine(150.0f, 400.0f, 250.0f, 500.0f, 2.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}



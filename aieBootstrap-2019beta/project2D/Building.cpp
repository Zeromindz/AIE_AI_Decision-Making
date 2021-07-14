#include "Building.h"

#include "DebugNew.h"

Building::Building()
{
	m_Texture = new aie::Texture("Assets/textures/Iso_Hut_001.png");
}


Building::Building(float _posX, float _posY)
{
	m_Texture = new aie::Texture("Assets/textures/Iso_Hut_001.png");

	m_PosX = _posX;
	m_PosY = _posY;
}

Building::~Building()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void Building::Draw(aie::Renderer2D* _renderer)
{
	_renderer->DrawSprite(m_Texture, m_PosX, m_PosY, 100, 100);
}

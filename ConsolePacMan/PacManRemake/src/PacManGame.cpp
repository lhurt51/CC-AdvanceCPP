#include "PacManGame.h"

#include "Scene/Map.h"

#include <Windows.h>

bool PacManGame::OnUserCreate()
{
	m_fPlayerX = 10.0f;
	m_fPlayerY = 10.0f;
	m_Sprite = new GameEngine::Sprite(L"res/PacManMap.scene");
	/*
	m_Sprite = new GameEngine::Sprite(4, 4);
	m_Sprite->SetGlyph(0, 0, L'#');
	m_Sprite->SetColor(0, 0, GameEngine::BG_CYAN);
	m_Sprite->SetGlyph(3, 3, L'#');
	m_Sprite->SetColor(3, 3, GameEngine::BG_GREEN);
	m_Sprite->Save(L"res/Tmp.scene");
	*/
	return true;
}

bool PacManGame::OnUserUpdate(float fElapsedTime)
{
	if (m_Keys[VK_LEFT].bHeld)
		m_fPlayerX -= 15.0f * fElapsedTime;
	if (m_Keys[VK_RIGHT].bHeld)
		m_fPlayerX += 15.0f * fElapsedTime;
	if (m_Keys[VK_UP].bHeld)
		m_fPlayerY -= 15.0f * fElapsedTime;
	if (m_Keys[VK_DOWN].bHeld)
		m_fPlayerY += 15.0f * fElapsedTime;
	
	Fill({ 0, 0 }, { m_ScreenWidth, m_ScreenHeight }, L' ', 0);
	FillTriangle(20, 0, 0, 25, 40, 25);
	FillCircle({ 75, 75 }, 10);
	Fill({ (int)m_fPlayerX, (int)m_fPlayerY }, { (int)m_fPlayerX + 5, (int)m_fPlayerY + 5 }, L' ', GameEngine::BG_DARK_GREY);
	DrawSprite({ 60, 20 }, m_Sprite);

	return true;
}

bool PacManGame::OnUserDestroy()
{
	Fill({ 0, 0 }, { m_ScreenWidth, m_ScreenHeight }, L' ', 0);
	delete m_Sprite;
	return true;
}

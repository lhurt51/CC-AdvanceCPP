#pragma once

#include <GameEngine.h>

class Map;

class PacManGame : public GameEngine::ConsoleGameEngine
{
public:

	PacManGame() { m_AppName = L"PacMan Remake"; }

protected:

	virtual bool OnUserCreate() override;
	virtual bool OnUserUpdate(float fElapsedTime) override;
	virtual bool OnUserDestroy() override;

private:

	//GameEngine::Sprite m_Sprite;

	float m_fPlayerX;
	float m_fPlayerY;

};


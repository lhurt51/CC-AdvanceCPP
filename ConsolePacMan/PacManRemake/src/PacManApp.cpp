#pragma once

#include <GameEngine.h>

class PacManApp : public GameEngine::Application
{
public:

	PacManApp()
	{

	}

	virtual ~PacManApp()
	{

	}

};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new PacManApp();
}
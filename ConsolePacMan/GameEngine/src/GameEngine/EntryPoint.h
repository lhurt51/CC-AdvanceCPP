#pragma once

#include <csignal>

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	// Initializing the logger and logging it
	GameEngine::Log::Init();
	GE_CORE_WARN("Initialized Log!");

	// Creating our app & running it
	auto app = GameEngine::CreateApplication();
	app->Run();
	// Deleting our app then closing the program
	delete app;
	return 0;
}

#endif

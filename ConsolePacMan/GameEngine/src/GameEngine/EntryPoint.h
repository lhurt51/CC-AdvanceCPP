#pragma once

#include <csignal>

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

void signalHandler(int signum)
{
	// Log the signal
	GE_CORE_ERROR("Program interupted ({0})", signum);

	// TODO: Clean up

	// Exit with signal
	exit(signum);
}

int main(int argc, char** argv)
{
	// Trying to catch exit signals
	signal(SIGINT, signalHandler);
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

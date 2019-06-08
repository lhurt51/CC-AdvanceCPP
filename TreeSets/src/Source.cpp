#include "Game\Game.hpp"

#include <SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <chrono>
#include <thread>

#ifdef main
	#undef main
#endif

int main(int argc, char** argv)
{
	Game game;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_Window* m_window = SDL_CreateWindow("Temp Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL);
	SDL_GLContext m_glContext = SDL_GL_CreateContext(m_window);

#ifdef TESTCODE
	std::cout << "Test" << std::endl;
	for (int i = 1; i < argc; ++i) 
		std::cout << argv[i] << std::endl;
#else
	argc = 0;
	argv = nullptr;
#endif

	std::cout << "Window Initilized" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	return 0;
}
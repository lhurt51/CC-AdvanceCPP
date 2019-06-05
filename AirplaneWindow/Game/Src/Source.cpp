/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 06/04/2019																	*
*																				*
* Assignment Requirement:														*
* 		Create a program using class or classes to simulate the flying of an	*
*		ASCII airplane across and ASCII frame with clouds.						*
*																				*
*		- Submit the source code and executable.								*
*																				*
\*******************************************************************************/

#include "Game.hpp"

Game *game = nullptr;

int main(int argc, char **argv)
{
	const int FPS = 100;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Airplane Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}
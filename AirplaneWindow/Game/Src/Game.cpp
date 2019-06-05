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
#include "TextureManager.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "AssetManager.h"

#include <cstdlib>
#include <ctime>

Manager		manager;

bool Game::isRunning = false;

SDL_Rect Game::camera = { 0, 0, 2048, 1080 };

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());
auto& background(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;

	srand(time(NULL));

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised! ..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	assets->AddTexture("plane", "assets/airplane.png");
	assets->AddTexture("background", "assets/clouds.png");
	
	player.addComponent<TransformComponent>(300, (rand() % (2160 - 1000)), 600, 1000, 0.75f);
	player.addComponent<SpriteComponent>("plane", SDL_FLIP_HORIZONTAL);
	player.addComponent<PlaneComponent>();
	player.addGroup(groupPlayers);

	background.addComponent<TransformComponent>(0, 0, 2160, 4096, 1.0f);
	background.addComponent<SpriteComponent>("background");
	background.addGroup(groupBackground);
}

auto& backgrounds(manager.getGroup(Game::groupBackground));
auto& players(manager.getGroup(Game::groupPlayers));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	camera.x = player.getComponent<TransformComponent>().position.x - 275;
	camera.y = player.getComponent<TransformComponent>().position.y - 175;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;

	if (player.getComponent<TransformComponent>().position.x > 2048 + 1200)
		isRunning = false;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& b : backgrounds)
	{
		b->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}

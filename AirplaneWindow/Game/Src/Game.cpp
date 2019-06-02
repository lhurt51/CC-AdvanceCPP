#include "Game.hpp"
#include "TextureManager.h"
#include "Scene.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"

Manager		manager;
Scene*		scene;

bool Game::isRunning = false;

SDL_Rect Game::camera = { 0, 0, 1100, 1200 };

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

auto& player(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;

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

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("projectile", "assets/circle.png");
	assets->AddTexture("plane", "assets/airplane.png");

	scene = new Scene("terrain", 3, 32);

	scene->loadScene("assets/map.map", 25, 20);
	
	player.addComponent<TransformComponent>(500, 300, 600, 1000, 0.75f);
	player.addComponent<SpriteComponent>("plane", false);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("plane");
	player.addGroup(groupPlayers);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playerCol))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 275;
	camera.y = player.getComponent<TransformComponent>().position.y - 175;

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w) camera.x = camera.w;
	if (camera.y > camera.h) camera.y = camera.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
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

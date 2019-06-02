#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game
{

	int count;
	SDL_Window *window;

public:

	static bool isRunning;
	static SDL_Rect camera;

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

	Game();
	~Game();

	void init(const char * title, int xPos, int yPos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };
};


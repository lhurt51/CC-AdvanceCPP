#pragma once

#include "Game.hpp"

class GameObject
{

	int xpos;
	int ypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

public:

	GameObject(const char* texturesSheet, int x, int y);
	~GameObject();

	void		update();
	void		render();

};


#pragma once

#include "../TextureManager.h"
#include "../Vector2D.h"
#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tsize, int tscale, std::string id)
	{
		texture = Game::assets->getTexture(id);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = tsize * tscale;
	}

	~TileComponent()
	{
	}

	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};
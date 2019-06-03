#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include "AssetManager.h"

#include <map>

class SpriteComponent : public Component
{

	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(std::string id) : transform(nullptr), texture(nullptr), srcRect(), destRect()
	{
		setTex(id);
	}

	SpriteComponent(std::string id, SDL_RendererFlip inSpriteFlip) : transform(nullptr), texture(nullptr), srcRect(), destRect()
	{
		setTex(id);
		spriteFlip = inSpriteFlip;
	}

	~SpriteComponent()
	{
	}

	void setTex(std::string id)
	{
		texture = Game::assets->getTexture(id);
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;

		destRect.w = static_cast<int>(transform->width * transform->scale);
		destRect.h = static_cast<int>(transform->height * transform->scale);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

};
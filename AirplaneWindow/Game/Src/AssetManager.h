#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager
{

	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;

public:

	AssetManager(Manager * man);
	~AssetManager();

	// Gameobjects
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string id);


};


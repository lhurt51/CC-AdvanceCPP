#pragma once

#include <string>

class Scene
{
	
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;

public:

	Scene(std::string tID, int ms, int ts);
	~Scene(void);

	void loadScene(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);

};


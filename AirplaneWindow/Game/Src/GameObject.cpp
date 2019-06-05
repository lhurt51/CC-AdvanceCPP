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

#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char * texturesSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesSheet);

	xpos = x;
	ypos = y;

	srcRect.h = 911;
	srcRect.w = 2403;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = static_cast<int>(srcRect.w * 0.25);
	destRect.h = static_cast<int>(srcRect.h * 0.25);
}

GameObject::~GameObject()
{
	return;
}

void GameObject::update()
{
	xpos++;
	ypos++;

	
	destRect.x = xpos;
	destRect.y = ypos;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

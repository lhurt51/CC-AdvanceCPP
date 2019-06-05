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

#include "Collision.h"
#include "ECS\Components.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent & colA, const ColliderComponent & colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit-> " << colB.tag << std::endl;
		return true;
	}
	return false;
}

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

#include "ECS.h"

void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

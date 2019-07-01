/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 06/08/2019																	*
*																				*
* Assignment Requirement:														*
* 	This homework will be a very simple scheduler.								*
*																				*
*	-The scheduler shall create three threads									*
*	-Each thread shall compute a random millisecond delay between 0 and 4		*
*		seconds																	*
*	-The main function shall run through the scheduler 5 times					*
*	-Each time of the scheduler shall delay for 2 seconds						*
*	-At the end of 2 seconds, the scheduler shall kill any threads still		*
*		running																	*
*	-The scheduler shall delay for an additional 1 second before restarting the	*
*		process																	*
*	-At each time of the scheduler, the scheduler shall restart the threads		*
*	-The scheduler shall display the current time and a message that the		*
*		schedule started														*
*	-Each thread shall display the current time with a message that it had		*
*		started																	*
*	-Each thread shall display the current time with a message of when it had	*
*		finished or interrupt to end by the scheduler							*
*																				*
\*******************************************************************************/

#include "PacManGame.h"

int main()
{
	PacManGame game;
	game.ConstructConsole(GameEngine::Vector2D<int>{160, 100}, GameEngine::Vector2D<int>(8, 8));
	game.Start();

	return 0;
 }

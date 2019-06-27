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

#include "GameEngine.h"

#include <Windows.h>

class Demo : public GameEngine::ConsoleGameEngine
{
public:

	Demo() { m_AppName = L"PacMan Remake"; }

protected:

	virtual bool OnUserCreate()
	{
		m_fPlayerX = 10.0f;
		m_fPlayerY = 10.0f;
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		if (m_Keys[VK_LEFT].bHeld)
			m_fPlayerX -= 15.0f * fElapsedTime;
		if (m_Keys[VK_RIGHT].bHeld)
			m_fPlayerX += 15.0f * fElapsedTime;
		if (m_Keys[VK_UP].bHeld)
			m_fPlayerY -= 15.0f * fElapsedTime;
		if (m_Keys[VK_DOWN].bHeld)
			m_fPlayerY += 15.0f * fElapsedTime;

		Fill(0, 0, m_ScreenWidth, m_ScreenHeight, L' ', 0);
		FillTriangle(20, 0, 0, 25, 40, 25);
		FillCircle(75, 75, 10);
		Fill((int)m_fPlayerX, (int)m_fPlayerY, (int)m_fPlayerX + 5, (int)m_fPlayerY + 5, L' ', GameEngine::BG_DARK_GREY);

		return true;
	}

private:

	float m_fPlayerX;
	float m_fPlayerY;

};

int main()
{
	Demo game;
	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	return 0;
 }

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

#include <iostream>
#include <chrono>
#include <mutex>
#include <iomanip>

#include "Scheduler/Scheduler.hpp"

std::mutex logMu;

void shared_print(std::string msg)
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	logMu.lock(); // Guard function from exceptions
	std::cout << std::put_time(std::localtime(&now), "%Y-%m-%d %X - ") << msg.c_str() << std::endl;
	logMu.unlock();
}

int main()
{
	// For Scheduler { Task(shared_print), Task(shared_print), Task(shared_print) }
	Scheduler s({ Task(shared_print), Task(shared_print), Task(shared_print) });
	// Printing program initialization
	std::cout << "Program Initilized" << std::endl;
	std::cout << "Concurrent Threads #" << std::thread::hardware_concurrency() << std::endl;
	
	// Run the scheduler
	s.Run();

	// Printing program destruction
	std::cout << "Main: THE END" << std::endl;
	std::cout << "Program Destroyed" << std::endl;

	return 0;
 }

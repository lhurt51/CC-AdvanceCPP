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
#include <string>
#include <thread>
#include <chrono>
#include <future>

#include <mutex>
std::mutex mu;
void shared_print(std::string msg)
{
	std::lock_guard<std::mutex> guard(mu); // Guard function from exceptions
	std::cout << msg.c_str() << std::endl;
}

void fun1()
{
	shared_print("Thread: Function sleeping for 1 second");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	shared_print("Thread: Function returning");
}

int main()
{
	// Printing program initialization
	std::cout << "Program Initilized" << std::endl;

	std::cout << "# of threads: " << std::thread::hardware_concurrency() << std::endl;
	auto fut = std::async(fun1);
	auto count = 1;
	while (fut.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
		shared_print(std::string("Main: ") + std::to_string(count++));
	shared_print(std::string("Main: Finished with a count of: ") + std::to_string(count));

	// Printing program destruction
	std::cout << "Program Destroyed" << std::endl;

	return 0;
 }
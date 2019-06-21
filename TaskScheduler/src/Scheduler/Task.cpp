#include "Task.hpp"

#include <iostream>
#include <thread>

unsigned int Task::taskNum = 0;

Task::Task(logFunction fnc) : m_OutFn(fnc), m_TaskId(++Task::taskNum)
{
}

Task::~Task()
{
	--Task::taskNum;
};

void Task::Process(std::atomic<bool>& isRunning)
{
	// Printing the threads info
	m_OutFn("Thread #" + std::to_string(m_TaskId) + " function sleeping for (milliseconds): - " + std::to_string(m_Delay));
	// Waiting for delay to complete or for is running to be set to false
	while (m_Delay > 0 && isRunning)
	{
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(10));
		m_Delay -= 10;
	}
	// Printing exiting info
	m_OutFn("Thread #" + std::to_string(m_TaskId) + " function " + ((isRunning) ? "finnished" : "interrupted") + " - " + std::to_string(m_Delay));
}
#pragma once

#include <atomic>
#include <string>

typedef void (*logFunction)(std::string text);

class Task
{
public:

	// Inilializing the task id and the logfunction
	Task(logFunction fnc);
	// Decrementing the task num
	~Task();

	// Setting the delay
	inline void SetDelay(unsigned int delay) { m_Delay = delay; };
	// Creating a process function that I can call asycronously
	void Process(std::atomic<bool>& isRunning);

public:

	// Storing the amount of tasks that we own
	static unsigned int taskNum;

private:

	// A task id for printing
	unsigned int m_TaskId;
	// Delay for 10 milli seconds and subtract 10 if atomic bool is false exit thread
	unsigned int m_Delay = 0;
	// Print function for multithreaded printing
	logFunction m_OutFn;

};
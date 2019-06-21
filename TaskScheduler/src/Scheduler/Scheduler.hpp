#pragma once

#include "Task.hpp"

#include <array>
#include <ctime>
#include <future>

class Scheduler
{
private:

	static const unsigned int MaxTasks = 3;
	static const unsigned int NumCycles = 5;

public:

	Scheduler(const std::array<Task, 3> & tasks) :
		m_Tasks(tasks),
		m_IsRunning(true)
	{
		srand(time(0));
	}
	~Scheduler() = default;

	inline void SetTaskDelay() { for (auto it = m_Tasks.begin(); it != m_Tasks.end(); ++it) it->SetDelay((rand() % 400) * 10); }

	inline void JoinThreads(std::array<std::future<void>, MaxTasks>& fTasks) { for (auto it = fTasks.begin(); it != fTasks.end(); ++it) it->get(); }

	void Run();
	inline void Reset() { m_IsRunning = true; }

private:

	std::atomic<bool> m_IsRunning;
	std::array<Task, MaxTasks> m_Tasks;

};
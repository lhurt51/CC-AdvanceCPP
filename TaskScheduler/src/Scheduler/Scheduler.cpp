#include "Scheduler.hpp"

#include <chrono>
#include <thread>

void shared_print(std::string msg);

void Scheduler::Run()
{
	std::array<std::future<void>, MaxTasks> fTasks;

	for (unsigned int i = 0; i < NumCycles; i++)
	{
		shared_print(std::string("Main: "));

		SetTaskDelay();

		for (unsigned int j = 0; j < MaxTasks; j++)
			fTasks[j] = std::async(std::launch::async, [](Task& in, std::atomic<bool>& isRunning) { in.Process(std::ref(isRunning)); }, std::ref(m_Tasks[j]), std::ref(m_IsRunning));

		// Compensation in milliseconds for the initialization lock time (Not Exact!)
		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(2190));
		m_IsRunning = false;

		JoinThreads(fTasks);

		shared_print(std::string("Main: "));

		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
		Reset();
	}
}
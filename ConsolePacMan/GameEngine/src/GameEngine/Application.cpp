#include "gepch.h"
#include "Application.h"

#include <chrono>
#include <thread>

namespace GameEngine
{

	// Creating a Predefine for getting the time in ms
	using Clock = std::chrono::high_resolution_clock;
	#define TimeNowInMs std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count();

	// Creating a stack ECSmanager
	Manager ECSManager;

	// Creating a singleton class
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Assets = new AssetManager(&ECSManager);
		GE_CORE_ASSERT(m_Assets, "Failed to create assets manager!");

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = TimeNowInMs;
			TimeStep timeStep = time - m_LastFrameTime;
			while (timeStep <= 0.011)
			{
				time = TimeNowInMs;
				timeStep = time - m_LastFrameTime;
			}
			m_LastFrameTime = time;

			ECSManager.Refresh();
			ECSManager.Update(timeStep);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timeStep);

			m_Window->OnUpdate(timeStep);

			ECSManager.OnDraw();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));

		ECSManager.OnEvent(e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

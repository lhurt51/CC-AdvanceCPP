#include "gepch.h"
#include "Application.h"

#include <chrono>

namespace GameEngine
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			auto t1 = std::chrono::high_resolution_clock::now().time_since_epoch();
			float time = std::chrono::duration_cast<std::chrono::milliseconds>(t1).count();
			TimeStep timeStep = time - m_LastFrameTime;
			while (timeStep < 0.016)
			{
				auto t1 = std::chrono::high_resolution_clock::now().time_since_epoch();
				float time = std::chrono::duration_cast<std::chrono::milliseconds>(t1).count();
				timeStep = time - m_LastFrameTime;
			}
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timeStep);

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));

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

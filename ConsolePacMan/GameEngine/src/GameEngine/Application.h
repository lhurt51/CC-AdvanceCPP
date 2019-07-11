#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace GameEngine
{
	class Application
	{
	public:

		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		// void PushLayer(Layer* layer);
		// void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

	public:

		// Creating singleton of this app instance
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	private:

		static Application* s_Instance;

	};

	// To be defined externally
	Application* CreateApplication();

}


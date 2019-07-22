#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Core/TimeStep.h"

#include "Managers/AssetManager.h"

namespace GameEngine
{
	class Application
	{
	public:

		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

	public:

		// Creating singleton of this app instance
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindowClose(WindowCloseEvent& e);

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	public:

		AssetManager* m_Assets;

	private:

		static Application* s_Instance;

	};

	// To be defined externally
	Application* CreateApplication();

}


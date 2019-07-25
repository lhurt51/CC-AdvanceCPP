#pragma once

#include "Core.h"
#include "Core/TimeStep.h"
#include "Window.h"
#include "LayerStack.h"
#include "Managers/AssetManager.h"
// All Events Just for the Includes
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace GameEngine
{
	enum EntityGroupLabels : std::size_t
	{
		GroupMap,
		GroupPlayers,
		GroupEnemies,
		GroupColliders
	};

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


	public:

		AssetManager* m_Assets;

	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:

		static Application* s_Instance;

	};

	// To be defined externally
	Application* CreateApplication();

}


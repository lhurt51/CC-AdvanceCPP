#pragma once
#include "gepch.h"

#include "Core.h"
#include "Events/Event.h"

namespace GameEngine
{

	struct WindowProps
	{

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Game Engine", unsigned int width = 160, unsigned height = 60)
			: Title(title), Width(width), Height(height)
		{}

	};

	class Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		// Returns the platform specific window (Not entirely nessicary)
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};

}
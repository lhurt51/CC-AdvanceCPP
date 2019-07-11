#pragma once

#include "GameEngine/Window.h"

namespace GameEngine
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		inline void* GetNativeWindow() const override { return m_Console; }

	private:

		void WindowsWindow::Error(const wchar_t* msg);
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:

		int m_ScreenWidth;
		int m_ScreenHeight;
		CHAR_INFO* m_bufScreen;

		HANDLE m_OriginalConsole;
		CONSOLE_SCREEN_BUFFER_INFOEX m_OriginalConsoleInfo;
		CONSOLE_FONT_INFOEX m_OriginalFontInfo;

		HANDLE m_Console;
		HANDLE m_ConsoleIn;
		SMALL_RECT m_WindowRect;

		bool m_bConsoleInFocus = true;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}


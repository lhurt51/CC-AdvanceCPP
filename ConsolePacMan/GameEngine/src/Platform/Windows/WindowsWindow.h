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

		inline void* GetNativeWindow() const override { return m_Win; }
		inline const void* GetWindowInfo() const override { return &WindowsWindow::m_Data; }

	private:

		//void Error(const std::wstring& msg);
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
		static BOOL WINAPI CloseHandler(DWORD evt);

		VOID WINAPI KeyEventProc(KEY_EVENT_RECORD ker);
		VOID WINAPI MouseEventProc(MOUSE_EVENT_RECORD mer);
		VOID WINAPI ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr);

	private:

		HWND m_Win;

		HANDLE m_OriginalConsole;
		// CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
		// CONSOLE_FONT_INFO m_OriginalFontInfo;
		SMALL_RECT m_OldWindowRect;
		DWORD fdwSaveOldMode;

		HANDLE m_Console;
		HANDLE m_ConsoleIn;

		SMALL_RECT m_WindowRect;

		bool m_bConsoleInFocus = true;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			CHAR_INFO* m_bufScreen;

			EventCallbackFn EventCallback;
		};

		static WindowData m_Data;

	};
}


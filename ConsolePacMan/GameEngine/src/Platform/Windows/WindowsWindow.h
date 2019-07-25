#pragma once

#include "GameEngine/Window.h"

namespace GameEngine
{
	class WindowsWindow : public Window
	{
	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate(TimeStep ts) override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		inline const void* GetNativeWindow() const override { return m_Win; }
		inline void* GetWindowInfo() const override { return (void*)&m_Data; }

	private:

		//void Error(const std::wstring& msg);
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
		static BOOL WINAPI CloseHandler(DWORD evt);

		VOID WINAPI KeyEventProc(KEY_EVENT_RECORD ker);
		VOID WINAPI MouseEventProc(MOUSE_EVENT_RECORD mer);
		VOID WINAPI ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr);

	public:

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			CHAR_INFO* m_bufScreen;

			EventCallbackFn EventCallback;
		};

	private:

		HWND m_Win;

		struct WinInfo
		{
		public:
			// Handle to console Output
			HANDLE HConsole;
			// Window Rect to print to
			SMALL_RECT WindowRect;
			// Handle to console Input
			HANDLE HConsoleIn;
			// Input mode
			DWORD WindowMode;
			// Unused info for consoles
			// CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
			// CONSOLE_FONT_INFO m_OriginalFontInfo;
		};
		
		// Storing Old WinInfo
		WinInfo m_OldWinInfo;
		// Storing New WinInfo
		WinInfo m_NewWinInfo;

		bool m_bConsoleInFocus = true;

		WindowData m_Data;

	};
}


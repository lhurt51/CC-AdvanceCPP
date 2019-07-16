#include "gepch.h"
#include "WindowsWindow.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine
{
	WindowsWindow::WindowData WindowsWindow::m_Data;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		m_OriginalConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		m_ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
		m_Win = GetConsoleWindow();

		/*
		std::memset(m_KeyNewState, 0, 256 * sizeof(short));
		std::memset(m_KeyOldState, 0, 256 * sizeof(short));
		std::memset(m_Keys, 0, 256 * sizeof(sKeyState));

		m_MousePosX = 0;
		m_MousePosY = 0;
		*/
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		static auto tp1 = std::chrono::system_clock::now();
		static auto tp2 = std::chrono::system_clock::now();

		// Handle game timing
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		// Handle Mouse Input - Check for window events
		INPUT_RECORD inBuf[32];
		DWORD events = 0;
		GetNumberOfConsoleInputEvents(m_ConsoleIn, &events);
		if (events > 0)
			ReadConsoleInput(m_ConsoleIn, inBuf, events, &events);

		// Handle events - we only care about mouse clicks and movement for now
		for (DWORD i = 0; i < events; i++)
		{
			switch (inBuf[i].EventType)
			{
			case KEY_EVENT:
				KeyEventProc(inBuf[i].Event.KeyEvent);
				break;
			case MOUSE_EVENT:
				MouseEventProc(inBuf[i].Event.MouseEvent);
				break;
			case WINDOW_BUFFER_SIZE_EVENT:
				ResizeEventProc(inBuf[i].Event.WindowBufferSizeEvent);
				break;
			case FOCUS_EVENT:
				m_bConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
				break;
			case MENU_EVENT:   // disregard menu events For now
				break;
			default:
				break;
			}
		}

		// Update title & present screen buffer
		std::wstring appName = std::wstring(m_Data.Title.begin(), m_Data.Title.end());
		wchar_t s[256];
		swprintf_s(s, 256, L"github.com/lhurt51 - Console - %s - FPS: %3.2f", appName.c_str(), 1.0f / fElapsedTime);
		SetConsoleTitle((wchar_t*)s);
		// WriteConsoleOutput(m_Console, m_bufScreen, { (short)m_Data.Width, (short)m_Data.Height }, { 0, 0 }, &m_WindowRect);
	}

	/* Should check errors this way eventually! (First need to find more efficient wstring conversion)
	void WindowsWindow::Error(const std::wstring& msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		std::wstring newBuf(buf);
		ShutDown();
		GE_CORE_ASSERT(nullptr, "Error: {0}", std::string(msg.begin(), msg.end()), std::string(newBuf.begin(), newBuf.end()));
	}
	*/

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (m_OriginalConsole == INVALID_HANDLE_VALUE)
			GE_CORE_ASSERT(nullptr, "Windows Window:Init(): Current Console handle invalid");
		/*
		if (!GetConsoleScreenBufferInfo(m_OriginalConsole, &m_OriginalConsoleInfo))
			GE_CORE_ASSERT(nullptr, "Windows Window: Getting current Console Info");
		if (!GetCurrentConsoleFont(m_OriginalConsole, false, &m_OriginalFontInfo))
			GE_CORE_ASSERT(nullptr, "Windows Window: Getting current Console Font Info");
		*/
		if (!GetConsoleMode(m_ConsoleIn, &fdwSaveOldMode))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): Getting current Console Mode");


		if (m_Console == INVALID_HANDLE_VALUE)
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console handle invalid");

		// Interesting work around for the console set screen buffer size thanks to Jx9 and OneLoneCoder
		m_WindowRect = { 0, 0, (short)m_Data.Width - 1, (short)m_Data.Height - 1 };
		SetConsoleWindowInfo(m_Console, TRUE, &m_WindowRect);

		// Set the size of the screen buffer
		COORD coord = { (short)m_Data.Width, (short)m_Data.Height };
		if (!SetConsoleScreenBufferSize(m_Console, coord))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console set Console Screen Buffer");

		// Assign screen buffer to the console
		if (!SetConsoleActiveScreenBuffer(m_Console))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console set Console Active Screen Buffer");

		/* Currently not in use
		// Set font size now that the screen buffer has been assigned
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 8;
		cfi.dwFontSize.Y = 16;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;

		wcscpy_s(cfi.FaceName, L"Consolas");
		if (!SetCurrentConsoleFontEx(m_Console, false, &cfi))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console set Console Font Info");
		*/

		// Get screen buffer onfo. Then check the maximum allowed window size.
		// Throw error if the window has exceeded max deminsions
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(m_Console, &csbi))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console get Screen Buffer Info");
		if (m_Data.Height > csbi.dwMaximumWindowSize.Y)
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console Screen/Font Height Too Big");
		if (m_Data.Width > csbi.dwMaximumWindowSize.X)
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console Screen/Font Width Too Big");

		// Set Physical Console Window Size
		m_WindowRect = { 0, 0, (short)m_Data.Width - 1, (short)m_Data.Height - 1 };
		if (!SetConsoleWindowInfo(m_Console, TRUE, &m_WindowRect))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): New Console set Console Screen Buffer");

		// Set flags for mouse input
		if (!SetConsoleMode(m_ConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
			GE_CORE_ASSERT(nullptr, "Windows Window: Init(): Setting new Console Mode");

		// Allocate memory for screen buffer
		int size = m_Data.Width * m_Data.Height;
		m_Data.m_bufScreen = new CHAR_INFO[size];
		memset(m_Data.m_bufScreen, 0, sizeof(CHAR_INFO) * size);

		SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
	}

	void WindowsWindow::ShutDown()
	{
		//system("cls");
		if (m_Data.m_bufScreen) delete[] m_Data.m_bufScreen;
		if (!SetConsoleActiveScreenBuffer(m_OriginalConsole))
			GE_CORE_ASSERT(nullptr, "Windows Window: Shutdown(): Setting current Active Console");
		/*
		if (!SetConsoleScreenBufferInfo(m_OriginalConsole, &m_OriginalConsoleInfo))
			GE_CORE_ASSERT(nullptr, "Window Shutdown: Setting current ConsoleInfo");
		if (!SetCurrentConsoleFontEx(m_OriginalConsole, false, &m_OriginalFontInfo))
			GE_CORE_ASSERT(nullptr, "Window Shutdown: Setting current Mode");
		*/
		if (!SetConsoleMode(m_ConsoleIn, fdwSaveOldMode))
			GE_CORE_ASSERT(nullptr, "Windows Window: Shutdown(): Setting current Mode");
	}

	BOOL WINAPI WindowsWindow::CloseHandler(DWORD evt)
	{
		switch (evt)
		{
		case CTRL_BREAK_EVENT:
		case CTRL_SHUTDOWN_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_CLOSE_EVENT:
		{
			WindowCloseEvent event;
			m_Data.EventCallback(event);
			return true;
		}
		default:
			return false;
		}
	}

	VOID WINAPI WindowsWindow::KeyEventProc(KEY_EVENT_RECORD ker)
	{
		/* Should probably do this and check with this data for inputs
		// Handle Keyboard Input
		for (int i = 0; i < 256; i++)
		{
			m_KeyNewState[i] = GetAsyncKeyState(i);

			m_Keys[i].bPressed = false;
			m_Keys[i].bReleased = false;

			if (m_KeyNewState[i] != m_KeyOldState[i])
			{
				if (m_KeyNewState[i] & 0x8000)
				{
					m_Keys[i].bPressed = !m_Keys[i].bHeld;
					m_Keys[i].bHeld = true;
				}
				else
				{
					m_Keys[i].bReleased = true;
					m_Keys[i].bHeld = false;
				}
			}
			m_KeyOldState[i] = m_KeyNewState[i];
		}
		*/
		if(ker.bKeyDown)
		{
			KeyPressedEvent event(ker.wVirtualKeyCode, ker.wRepeatCount);
			m_Data.EventCallback(event);
		}
		else
		{
			KeyReleasedEvent event(ker.wVirtualKeyCode);
			m_Data.EventCallback(event);
		}
		if (ker.wVirtualKeyCode == VK_ESCAPE)
		{
			GE_CORE_INFO("Window Close Event");
			WindowCloseEvent event;
			m_Data.EventCallback(event);
		}
	}

	VOID WINAPI WindowsWindow::MouseEventProc(MOUSE_EVENT_RECORD mer)
	{
		switch (mer.dwEventFlags)
		{
		case 0:
		/* How I should be polling events
		for (int m = 0; m < 5; m++)
			m_MouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;

		for (int m = 0; m < 5; m++)
		{
			m_Mouse[m].bPressed = false;
			m_Mouse[m].bReleased = false;

			if (m_MouseNewState[m] != m_MouseOldState[m])
			{
				if (m_MouseNewState[m])
				{
					m_Mouse[m].bPressed = true;
						m_Mouse[m].bHeld = true;
				}
				else
				{
					m_Mouse[m].bReleased = true;
					m_Mouse[m].bHeld = false;
				}
			}
			m_MouseOldState[m] = m_MouseNewState[m];
		}
		*/
			if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				GE_CORE_INFO("left button press");
			}
			else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				GE_CORE_INFO("right button press");
			}
			break;
		case DOUBLE_CLICK:
			GE_CORE_INFO("double click");
			break;
		case MOUSE_MOVED:
		{
			/*
			m_MousePosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
			m_MousePosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
			*/
			MouseMovedEvent event((float)mer.dwMousePosition.X, (float)mer.dwMousePosition.X);
			m_Data.EventCallback(event);
			break;
		}
		case MOUSE_WHEELED:
			GE_CORE_INFO("vertical mouse wheel");
			break;
		default:
			break;
		}
	}

	VOID WINAPI WindowsWindow::ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
	{
		// TODO: Handle window buffer resize
		GE_CORE_INFO("Console screen buffer is {0} columns by {1} rows.", wbsr.dwSize.X, wbsr.dwSize.Y);
		WindowResizeEvent event(wbsr.dwSize.X, wbsr.dwSize.Y);
		m_Data.EventCallback(event);
	}

}


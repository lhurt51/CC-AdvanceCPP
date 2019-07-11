#include "gepch.h"
#include "WindowsWindow.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine
{

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		// m_ScreenWidth = 160;
		// m_ScreenHeight = 60;

		m_OriginalConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfoEx(m_OriginalConsole, &m_OriginalConsoleInfo);
		GetCurrentConsoleFontEx(m_OriginalConsole, false, &m_OriginalFontInfo);

		m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		m_ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

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
			case FOCUS_EVENT:
			{
				m_bConsoleInFocus = inBuf[i].Event.FocusEvent.bSetFocus;
				break;
			}
			case KEY_EVENT:
			{
			case WM_KEYDOWN:
				break;
			case WM_KEYUP:
				switch (inBuf[i].Event.KeyEvent.wVirtualKeyCode)
				{
					/* if escape key is pressed*/
				case VK_ESCAPE:
					return;

				case VK_LEFT:
					// Process the LEFT ARROW key. 
					break;

				case VK_RIGHT:
					// Process the RIGHT ARROW key. 
					break;

				case VK_UP:
					// Process the UP ARROW key. 
					break;

				case VK_DOWN:
					// Process the DOWN ARROW key. 
					break;

				case VK_HOME:
					// Process the HOME key. 

					break;

				case VK_END:
					// Process the END key. 
					break;

				case VK_INSERT:
					// Process the INS key. 
					break;

				case VK_DELETE:
					// Process the DEL key. 
					break;

				case VK_F2:
					// Process the F2 key. 
					break;

					// Process other non-character keystrokes. 
				default:
					break;
				}
				break;
			}
			case WINDOW_BUFFER_SIZE_EVENT:
				// TODO: Handle window buffer resize
				WINDOW_BUFFER_SIZE_RECORD wbsr = inBuf[i].Event.WindowBufferSizeEvent;
				GE_CORE_INFO("Console screen buffer is {0} columns by {1} rows.", wbsr.dwSize.X, wbsr.dwSize.Y);
				break;
			default:
				// No need to process anything
				break;
			}
		}

		// Update title & present screen buffer
		std::wstring appName = std::wstring(m_Data.Title.begin(), m_Data.Title.begin());
		wchar_t s[256];
		swprintf_s(s, 256, L"github.com/lhurt51 - Console Game Engine - %s - FPS: %3.2f", appName.c_str(), 1.0f / fElapsedTime);
		SetConsoleTitle((wchar_t*)s);
		WriteConsoleOutput(m_Console, m_bufScreen, { (short)m_ScreenWidth, (short)m_ScreenHeight }, { 0, 0 }, &m_WindowRect);
	}

	void WindowsWindow::Error(const wchar_t* msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		SetConsoleActiveScreenBuffer(m_OriginalConsole);
		SetConsoleScreenBufferInfoEx(m_OriginalConsole, &m_OriginalConsoleInfo);
		SetCurrentConsoleFontEx(m_Console, false, &m_OriginalFontInfo);
		// GE_CORE_ASSERT(false, "Error: {0}\n\t{1}\n", msg, buf);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		GE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (m_Console == INVALID_HANDLE_VALUE)
			return Error(L"Bad Handle");

		m_ScreenWidth = props.Width;
		m_ScreenHeight = props.Height;

		// Interesting work around for the console set screen buffer size thanks to Jx9 and OneLoneCoder
		m_WindowRect = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(m_Console, TRUE, &m_WindowRect);

		// Set the size of the screen buffer
		COORD coord = { (short)m_ScreenWidth, (short)m_ScreenHeight };
		if (!SetConsoleScreenBufferSize(m_Console, coord))
			Error(L"SetConsoleScreenBufferSize");

		// Assign screen buffer to the console
		if (!SetConsoleActiveScreenBuffer(m_Console))
			return Error(L"SetConsoleActiveScreenBuffer");

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
			return Error(L"SetCurrentConsoleFontEx");
		// Get screen buffer onfo. Then check the maximum allowed window size.
		// Throw error if the window has exceeded max deminsions
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(m_Console, &csbi))
			return Error(L"GetConsoleScreenBufferInfo");
		if (m_ScreenHeight > csbi.dwMaximumWindowSize.Y)
			return Error(L"Screen/Font Height Too Big");
		if (m_ScreenWidth > csbi.dwMaximumWindowSize.X)
			return Error(L"Screen/Font Width Too Big");

		// Set Physical Console Window Size
		m_WindowRect = { 0, 0, (short)m_ScreenWidth - 1, (short)m_ScreenHeight - 1 };
		if (!SetConsoleWindowInfo(m_Console, TRUE, &m_WindowRect))
			return Error(L"SetConsoleWindowInfo");

		// Set flags for mouse input
		if (!SetConsoleMode(m_ConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
			return Error(L"SetConsoleMode");

		// Allocate memory for screen buffer
		int size = m_ScreenWidth * m_ScreenHeight;
		m_bufScreen = new CHAR_INFO[size];
		memset(m_bufScreen, 0, sizeof(CHAR_INFO) * size);
	}

	void WindowsWindow::ShutDown()
	{
		system("cls");
		/*
		SetConsoleActiveScreenBuffer(m_OriginalConsole);
		SetConsoleScreenBufferInfoEx(m_OriginalConsole, &m_OriginalConsoleInfo);
		SetCurrentConsoleFontEx(m_Console, false, &m_OriginalFontInfo);
		if (m_bufScreen) delete[] m_bufScreen;
		*/
	}

}


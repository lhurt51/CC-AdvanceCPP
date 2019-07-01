#include "gepch.h"
#include "ConsoleGameEngine.h"

#include "Math/Vector.h"

#include <stdlib.h>

namespace GameEngine
{

	std::atomic<bool> ConsoleGameEngine::m_bAtomicActive(false);
	std::condition_variable ConsoleGameEngine::m_GameFinished;
	std::mutex ConsoleGameEngine::m_GameMu;

	ConsoleGameEngine::ConsoleGameEngine()
	{
		m_ScreenWidth = 80;
		m_ScreenHeight = 30;

		m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
		m_ConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

		std::memset(m_KeyNewState, 0, 256 * sizeof(short));
		std::memset(m_KeyOldState, 0, 256 * sizeof(short));
		std::memset(m_Keys, 0, 256 * sizeof(sKeyState));

		m_MousePosX = 0;
		m_MousePosY = 0;

		m_bEnableSound = false;
		m_AppName = L"Default";
	}

	ConsoleGameEngine::~ConsoleGameEngine()
	{
		system("CLS");
		SetConsoleActiveScreenBuffer(m_OriginalConsole);
		delete[] m_bufScreen;
	}

	int ConsoleGameEngine::ConstructConsole(const Vector2D<int>& winDem, const Vector2D<int>& fontSize)
	{
		if (m_Console == INVALID_HANDLE_VALUE)
			return Error(L"Bad Handle");

		m_ScreenWidth = winDem.x;
		m_ScreenHeight = winDem.y;

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
		cfi.dwFontSize.X = fontSize.x;
		cfi.dwFontSize.Y = fontSize.y;
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

		SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
		return 1;
	}

	void ConsoleGameEngine::Draw(const Vector2D<int>& pos, short c, short col)
	{
		if (pos.x >= 0 && pos.x < m_ScreenWidth && pos.y >= 0 && pos.y < m_ScreenHeight)
		{
			m_bufScreen[pos.y * m_ScreenWidth + pos.x].Char.UnicodeChar = c;
			m_bufScreen[pos.y * m_ScreenWidth + pos.x].Attributes = col;
		}
	}

	void ConsoleGameEngine::Fill(const Vector2D<int>& pos1, const Vector2D<int>& pos2, short c, short col)
	{
		Vector2D<int> tmp1 = pos1;
		Vector2D<int> tmp2 = pos2;
		Clip(tmp1);
		Clip(tmp2);
		for (int x = tmp1.x; x < tmp2.x; x++)
			for (int y = tmp1.y; y < tmp2.y; y++)
				Draw({x, y}, c, col);
	}

	void ConsoleGameEngine::DrawString(const Vector2D<int>& pos, std::wstring c, short col)
	{
		for (size_t i = 0; i < c.size(); i++)
		{
			m_bufScreen[pos.y * m_ScreenWidth + pos.x + (int)i].Char.UnicodeChar = c[i];
			m_bufScreen[pos.y * m_ScreenWidth + pos.x + (int)i].Attributes = col;
		}
	}

	void ConsoleGameEngine::DrawStringAlpha(const Vector2D<int>& pos, std::wstring c, short col)
	{
		for (size_t i = 0; i < c.size(); i++)
		{
			if (c[i] != L' ')
			{
				m_bufScreen[pos.y * m_ScreenWidth + pos.x + (int)i].Char.UnicodeChar = c[i];
				m_bufScreen[pos.y * m_ScreenWidth + pos.x + (int)i].Attributes = col;
			}
		}
	}

	void ConsoleGameEngine::Clip(Vector2D<int>& pos)
	{
		if (pos.x < 0) pos.x = 0;
		if (pos.x > m_ScreenWidth) pos.x = m_ScreenWidth;
		if (pos.y < 0) pos.y = 0;
		if (pos.y > m_ScreenHeight) pos.y = m_ScreenHeight;
	}

	void ConsoleGameEngine::DrawLine(const Vector2D<int>& pos1, const Vector2D<int>& pos2, short c, short col)
	{
		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = pos2.x - pos1.x;
		dy = pos2.y - pos1.y;
		dx1 = abs(dx);
		dy1 = abs(dy);
		px = 2 * dy1 - dx1;
		py = 2 * dx1 - dy1;

		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = pos1.x;
				y = pos1.y;
				xe = pos2.x;
			}
			else
			{
				x = pos2.x;
				y = pos2.y;
				xe = pos1.x;
			}

			Draw({x, y}, c, col);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						y = y + 1;
					else
						y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				Draw({x, y}, c, col);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = pos1.x;
				y = pos1.y;
				ye = pos2.y;
			}
			else
			{
				x = pos2.x;
				y = pos2.y;
				ye = pos1.y;
			}
			Draw({x, y}, c, col);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
						x = x + 1;
					else
						x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				Draw({ x, y }, c, col);
			}
		}
	}

	void ConsoleGameEngine::DrawTriangle(const Vector2D<int>& pos1, const Vector2D<int>& pos2, const Vector2D<int>& pos3, short c, short col)
	{
		DrawLine(pos1, pos2, c, col);
		DrawLine(pos2, pos3, c, col);
		DrawLine(pos3, pos1, c, col);
	}

	// https://www.avrfreaks.net/sites/default/files/triangles.c
	void ConsoleGameEngine::FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c, short col)
	{
		auto SWAP = [](int& x, int& y) { int t = x; x = y; y = t; };
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw({ i, ny }, c, col); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		// Sort vertices
		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

		t1x = t2x = x1; y = y1;   // Starting points
		dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) {   // swap values
			SWAP(dx1, dy1);
			changed1 = true;
		}
		if (dy2 > dx2) {   // swap values
			SWAP(dy2, dx2);
			changed2 = true;
		}

		e2 = (int)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);    // Draw line from min to max points found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		// Second half
		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}

	void ConsoleGameEngine::DrawCircle(const Vector2D<int>& pos, int r, short c, short col)
	{
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;

		if (!r) return;
		while (y >= x)
		{
			Draw({ pos.x - x, pos.y - y }, c, col); // Upper left left
			Draw({ pos.x - y, pos.y - x }, c, col); // Upper upper left
			Draw({ pos.x + y, pos.y - x }, c, col); // Upper upper right
			Draw({ pos.x + x, pos.y - y }, c, col); // Upper right right
			Draw({ pos.x - x, pos.y + y }, c, col); // Lower left left
			Draw({ pos.x - y, pos.y + x }, c, col); // Lower lower left
			Draw({ pos.x + y, pos.y + x }, c, col); // Lower lower right
			Draw({ pos.x + x, pos.y + y }, c, col); // Lower right right
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void ConsoleGameEngine::FillCircle(const Vector2D<int>& pos, int r, short c, short col)
	{
		int x = 0;
		int y = r;
		int p = 3 - 2 * r;

		if (!r) return;
		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				Draw({ i, ny }, c, col);
		};

		// Draws by using scan-lines
		while (y >= x)
		{
			drawline(pos.x - x, pos.x + x, pos.y - y);
			drawline(pos.x - y, pos.x + y, pos.y - x);
			drawline(pos.x - x, pos.x + x, pos.y + y);
			drawline(pos.x - y, pos.x + y, pos.y + x);
			if (p < 0) p += 4 * x++ + 6;
			else p += 4 * (x++ - y--) + 10;
		}
	}

	void ConsoleGameEngine::DrawSprite(const Vector2D<int>& pos, Sprite* sprite)
	{
		if (sprite == nullptr)
			return;

		for (int i = 0; i < sprite->nWidth; i++)
		{
			for (int j = 0; j < sprite->nHeight; j++)
			{
				if (sprite->GetGlyph(i, j) != L' ')
					Draw({ pos.x + i, pos.y + j }, sprite->GetGlyph(i, j), sprite->GetColor(i, j));
			}
		}
	}

	void ConsoleGameEngine::DrawPartialSprite(const Vector2D<int>& pos, Sprite* sprite, const Vector2D<int>& opos, const Vector2D<int>& size)
	{
		if (sprite == nullptr)
			return;

		for (int i = 0; i < size.x; i++)
		{
			for (int j = 0; j < size.y; j++)
			{
				if (sprite->GetGlyph(i + opos.x, j + opos.y) != L' ')
					Draw({ pos.x + i, pos.y + j }, sprite->GetGlyph(i + opos.x, j + opos.y), sprite->GetColor(i + opos.x, j + opos.y));
			}
		}
	}

	void ConsoleGameEngine::DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r, float s, short col, short c)
	{
		// Create translated model vector of coordinate pairs
		std::vector<std::pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].second * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}

		// Scale
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * 5;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * 5;
		}

		// Translate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine({ (int)vecTransformedCoordinates[i % verts].first, (int)vecTransformedCoordinates[i % verts].second }, { (int)vecTransformedCoordinates[j % verts].first, (int)vecTransformedCoordinates[j % verts].second }, c, col);
		}
	}

	void ConsoleGameEngine::Start()
	{
		// Staring the game thread
		m_bAtomicActive = true;
		std::thread t = std::thread(&ConsoleGameEngine::GameThread, this);

		// Wait for threa to be exited
		t.join();
	}

	int ConsoleGameEngine::ScreenWidth()
	{
		return m_ScreenWidth;
	}

	int ConsoleGameEngine::ScreenHeight()
	{
		return m_ScreenHeight;
	}

	void ConsoleGameEngine::GameThread()
	{
		// Create user resources before thread
		if (!OnUserCreate())
			m_bAtomicActive = false;

		auto tp1 = std::chrono::system_clock::now();
		auto tp2 = std::chrono::system_clock::now();

		while (m_bAtomicActive)
		{
			// Handle game timing
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();

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
				case MOUSE_EVENT:
				{
					switch (inBuf[i].Event.MouseEvent.dwEventFlags)
					{
					case MOUSE_MOVED:
					{
						m_MousePosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
						m_MousePosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
						break;
					}
					case 0:
					{
						for (int m = 0; m < 5; m++)
							m_MouseNewState[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
						break;
					}
					default:
						break;
					}
					break;
				}
				default:
					// No need to process anything
					break;
				}
			}

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

			// Handle Frame Update
			if (!OnUserUpdate(fElapsedTime))
				m_bAtomicActive = false;

			// Update title & present screen buffer
			wchar_t s[256];
			swprintf_s(s, 256, L"github.com/lhurt51 - Console Game Engine - %s - FPS: %3.2f", m_AppName.c_str(), 1.0f / fElapsedTime);
			SetConsoleTitle(s);
			WriteConsoleOutput(m_Console, m_bufScreen, { (short)m_ScreenWidth, (short)m_ScreenHeight }, { 0, 0 }, & m_WindowRect);
		}

		// Allow the user to free all resources if they override destroy functionality
		if (OnUserDestroy())
		{
			// User has permitter destory, so exit
			delete[] m_bufScreen;
			SetConsoleActiveScreenBuffer(m_OriginalConsole);
			m_GameFinished.notify_one();
		}
		else
		{
			// User denied destroy for some reason so continue running
			m_bAtomicActive = true;
		}

	}

	int ConsoleGameEngine::Error(const wchar_t* msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		SetConsoleActiveScreenBuffer(m_OriginalConsole);
		wprintf(L"Error: %s\n\t%s\n", msg, buf);
		return 0;
	}

	BOOL ConsoleGameEngine::CloseHandler(DWORD evt)
	{
		// This is called is seprate OS thread
		// Only allowed to exit when the game is done cleaning up
		// Otherwise!!! process is killed before OnUserDestory() is done
		if (evt == CTRL_CLOSE_EVENT)
		{
			m_bAtomicActive = false;

			// Wait for thread to be exited
			std::unique_lock<std::mutex> ul(m_GameMu);
			m_GameFinished.wait(ul);
		}
		return true;
	}

}
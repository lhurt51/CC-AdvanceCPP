#pragma once

#include "gepch.h"
#include "Sprite.h"

namespace GameEngine
{
	// Forward declaring classes and types
	template<typename T> class		Vector2D;

	class ConsoleGameEngine
	{
	public:

		ConsoleGameEngine();

		virtual ~ConsoleGameEngine();

		inline void EnableSound() { m_bEnableSound = true; }

		int ConstructConsole(const Vector2D<int>& winDem, const Vector2D<int>& fontSize);

		virtual void Draw(const Vector2D<int>& pos, short c = 0x2588, short col = 0x000F);

		void Fill(const Vector2D<int>& pos1, const Vector2D<int>& pos2, short c = 0x2588, short col = 0x000F);

		void DrawString(const Vector2D<int>& pos, std::wstring c, short col = 0x000F);

		void DrawStringAlpha(const Vector2D<int>& pos, std::wstring c, short col = 0x000F);

		void Clip(Vector2D<int>& pos);

		void DrawLine(const Vector2D<int>& pos1, const Vector2D<int>& pos2, short c = 0x2588, short col = 0x000F);

		void DrawTriangle(const Vector2D<int>& pos1, const Vector2D<int>& pos2, const Vector2D<int>& pos3, short c = 0x2588, short col = 0x000F);

		void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short c = 0x2588, short col = 0x000F);

		void DrawCircle(const Vector2D<int>& pos, int r, short c = 0x2588, short col = 0x000F);

		void FillCircle(const Vector2D<int>& pos, int r, short c = 0x2588, short col = 0x000F);

		void DrawSprite(const Vector2D<int>& pos, Sprite* sprite);

		void DrawPartialSprite(const Vector2D<int>& pos, Sprite* sprite, const Vector2D<int>& opos, const Vector2D<int>& size);

		void DrawWireFrameModel(const std::vector<std::pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, short col = FG_WHITE, short c = PIXEL_SOLID);

		void Start();

		int ScreenWidth();

		int ScreenHeight();

	private:

		void GameThread();

	public:

		// User MUST Override THESE!!
		virtual bool OnUserCreate() = 0;
		virtual bool OnUserUpdate(float fElapsedTime) = 0;

		// Optional for clean up
		virtual bool OnUserDestroy() { return true; }


	// Input layer... Needs to be abstracted
	protected:

		struct sKeyState
		{
			bool bPressed;
			bool bReleased;
			bool bHeld;
		} m_Keys[256], m_Mouse[5];

		int m_MousePosX, m_MousePosY;

	public:

		inline sKeyState GetKey(int nKeyID) { return m_Keys[nKeyID]; }
		inline int GetMouseX() { return m_MousePosX; }
		inline int GetMouseY() { return m_MousePosY; }
		inline sKeyState GetMouse(int nMouseButtonID) { return m_Mouse[nMouseButtonID]; }
		inline bool IsFocused() { return m_bConsoleInFocus; }

	protected:

		int Error(const wchar_t* msg);
		static BOOL CloseHandler(DWORD evt);

	protected:

		int m_ScreenWidth;
		int m_ScreenHeight;
		CHAR_INFO* m_bufScreen;
		std::wstring m_AppName;
		HANDLE m_OriginalConsole;
		CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
		HANDLE m_Console;
		HANDLE m_ConsoleIn;
		SMALL_RECT m_WindowRect;
		short m_KeyOldState[256] = { 0 };
		short m_KeyNewState[256] = { 0 };
		bool m_MouseOldState[5] = { 0 };
		bool m_MouseNewState[5] = { 0 };
		bool m_bConsoleInFocus = true;
		bool m_bEnableSound = false;

		// Needs static attributes because OnDestroy may be called on the OS because of special thread spawning
		static std::atomic<bool> m_bAtomicActive;
		static std::condition_variable m_GameFinished;
		static std::mutex m_GameMu;

	};
}
#include "gepch.h"
#include "WindowsInput.h"

#include "GameEngine/Application.h"

namespace GameEngine
{
	
	const unsigned short MSB = 0x8000;

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		if (GetAsyncKeyState(keycode) & MSB > 0)
			return true;
		return false;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		// TODO: Fix the mouse button input
		if (GetAsyncKeyState(button) & MSB > 0)
			return true;
		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient((HWND)Application::Get().GetWindow().GetNativeWindow(), &p);
		return { (float)p.x, (float)p.y };
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}

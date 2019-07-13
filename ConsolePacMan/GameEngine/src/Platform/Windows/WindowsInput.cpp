#include "gepch.h"
#include "WindowsInput.h"

namespace GameEngine
{
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return false;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return false;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		return std::pair<float, float>();
	}
	float WindowsInput::GetMouseXImpl()
	{
		return 0.0f;
	}
	float WindowsInput::GetMouseYImpl()
	{
		return 0.0f;
	}
}

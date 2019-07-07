#include "gepch.h"
#include "Application.h"

#include <iostream>

namespace GameEngine
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}

}

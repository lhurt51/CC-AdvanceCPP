#pragma once

#include <GameEngine.h>

// Project for acctually creating you game instance
class ExampleLayer : public GameEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
		// RenderCommand::SetClearColor(0x0080);
	}

	void OnUpdate(GameEngine::TimeStep ts) override
	{
		/* Rendering Settup TODO
		** RenderCommand::SetClearColor();
		** RenderCommand::Clear();
		**
		** Planning renderer code (High level class)
		** Renderer::BeginScene(camera, lights, environment);
		**
		** m_SquareShader->Bind();
		** Renderer::Submit(m_SquareVA);
		**
		** m_Shader->Bind();
		** Renderer::Submit(m_VertexArray);
		**
		** Renderer::EndScene();
		**
		** // Should be on a different thread
		** Renderer::Flush();
		*/

		GameEngine::RenderCommand::Clear();
		GameEngine::RenderCommand::DrawString({ 20, 20 }, L"Hello World", 0x0001);

		// GE_TRACE("Delta Time: {0}s ({1}ms)", ts, ts.GetMilliseconds());

		/*
		if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT))
			GE_TRACE("Key pressed left!");

		if (GameEngine::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT))
			GE_TRACE("Mouse button left pressed!");
		if (GameEngine::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_RIGHT))
			GE_TRACE("Mouse button right pressed!");
		*/

	}

	void OnEvent(GameEngine::Event& event) override
	{
		GameEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

	}

	bool OnKeyPressedEvent(GameEngine::KeyPressedEvent& event)
	{
		// --- Raw Input handling (Only updates every key press) ---
		if (event.GetKeyCode() == GE_KEY_LEFT)
			GE_TRACE("Key left pressed!");
		if (event.GetKeyCode() == GE_KEY_RIGHT)
			GE_TRACE("Key right pressed!");
		if (event.GetKeyCode() == GE_KEY_UP)
			GE_TRACE("Key up pressed!");
		if (event.GetKeyCode() == GE_KEY_DOWN)
			GE_TRACE("Key down pressed!");

		return false;
	}
};

class PacManApp : public GameEngine::Application
{
public:

	PacManApp()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~PacManApp() = default;

};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new PacManApp();
}
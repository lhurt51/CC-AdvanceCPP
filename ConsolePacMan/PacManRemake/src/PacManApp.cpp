#pragma once

#include <GameEngine.h>

// Project for acctually creating you game instance
class ExampleLayer : public GameEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
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

		if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT))
			GE_TRACE("Key pressed left!");

		if (GameEngine::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_LEFT))
			GE_TRACE("Key pressed left!");

		/*
		GE_TRACE("Delta Time: {0}s ({1}ms)", ts, ts.GetMilliseconds());

		if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT))
			m_CameraPos.x += m_CameraMoveSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_RIGHT))
			m_CameraPos.x -= m_CameraMoveSpeed * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_UP))
			m_CameraPos.y -= m_CameraMoveSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_DOWN))
			m_CameraPos.y += m_CameraMoveSpeed * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_Q))
			m_CameraRotation -= m_CameraRotSpeed * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_E))
			m_CameraRotation += m_CameraRotSpeed * ts;
		*/

	}

	void OnEvent(GameEngine::Event& event) override
	{
		GameEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));

	}

	bool OnKeyPressedEvent(GameEngine::KeyPressedEvent& event)
	{
		/*
		--- Raw Input handling (Only updates every key press) ---
		if (event.GetKeyCode() == GE_KEY_LEFT)
			m_CameraPos.x -= m_CameraSpeed;
		if (event.GetKeyCode() == GE_KEY_RIGHT)
			m_CameraPos.x += m_CameraSpeed;
		if (event.GetKeyCode() == GE_KEY_UP)
			m_CameraPos.y += m_CameraSpeed;
		if (event.GetKeyCode() == GE_KEY_DOWN)
			m_CameraPos.y -= m_CameraSpeed;
		*/

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

	virtual ~PacManApp()
	{

	}

};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new PacManApp();
}
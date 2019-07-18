#pragma once

#include <GameEngine.h>

// Project for acctually creating you game instance
class ExampleLayer : public GameEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Example")
	{
		m_Board = new GameEngine::Sprite(L"res/PacManMap.scene");
		// GameEngine::RenderCommand::SetClearColor(GameEngine::BG_DARK_GREY);
	}

	virtual ~ExampleLayer()
	{
		delete m_Board;
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

		// The input is in units/sec
		if (GameEngine::Input::IsKeyPressed(GE_KEY_A))
			m_Pos.x -= 12 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
			m_Pos.x += 12 * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
			m_Pos.y -= 20 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
			m_Pos.y += 20 * ts;

		GameEngine::RenderCommand::Clear();
		GameEngine::RenderCommand::DrawSprite({ 80 - m_Board->nWidth * 0.5, 30 - m_Board->nHeight * 0.5}, *m_Board);
		GameEngine::RenderCommand::DrawString(m_Pos, L"@", GameEngine::FG_DARK_CYAN);

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

	void OnEvent(GameEngine::Event& e) override
	{
		GameEngine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(GameEngine::KeyPressedEvent& event)
	{
		// --- Raw Input handling (Only updates every key press) ---
		/*
		if (event.GetKeyCode() == GE_KEY_LEFT)
			GE_TRACE("Key left pressed!");
		if (event.GetKeyCode() == GE_KEY_RIGHT)
			GE_TRACE("Key right pressed!");
		if (event.GetKeyCode() == GE_KEY_UP)
			GE_TRACE("Key up pressed!");
		if (event.GetKeyCode() == GE_KEY_DOWN)
			GE_TRACE("Key down pressed!");
		*/

		return false;
	}

private:

	GameEngine::Sprite* m_Board;
	glm::vec2 m_Pos = { 61, 25 };

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
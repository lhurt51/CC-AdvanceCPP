#pragma once

#include <GameEngine.h>

// Project for acctually creating you game instance
class ExampleLayer : public GameEngine::Layer
{
public:

	ExampleLayer()
		: Layer("Example"), board(GameEngine::Application::Get().m_Assets->GetManager().AddEntity())
	{}

	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override
	{
		board.AddComponent<GameEngine::TransformComponent>();
		board.AddComponent<GameEngine::SpriteComponent>("Map");
		board.AddComponent<GameEngine::KeyboardController>();
		auto& spriteSize = board.GetComponent<GameEngine::SpriteComponent>().sprite.size;
		board.GetComponent<GameEngine::TransformComponent>().position = { 80 - spriteSize.x * 0.5, 30 - spriteSize.y * 0.5 };
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
			m_Pos.x -= 10 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
			m_Pos.x += 10 * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
			m_Pos.y -= 10 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
			m_Pos.y += 10 * ts;

		// GameEngine::RenderCommand::SetClearColor(GameEngine::BG_BLACK);
		GameEngine::RenderCommand::Clear();
		board.OnDraw();
		GameEngine::RenderCommand::DrawString(m_Pos, L"@", GameEngine::FG_DARK_CYAN);

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

	GameEngine::Entity& board;
	glm::vec2 m_Pos = { 61, 25 };

};

// Simple overlay to print out app info
class ExampleOverlay : public GameEngine::Layer
{
public:

	ExampleOverlay()
		: Layer("ExampleOverlay")
	{}

	virtual ~ExampleOverlay() = default;

	void OnUpdate(GameEngine::TimeStep ts) override
	{
		GameEngine::RenderCommand::DrawString({ 1, 1 }, std::wstring(L"Delta Time: " + std::to_wstring(ts) + L"s (" + std::to_wstring(ts.GetMilliseconds()) + L"ms)"), GameEngine::FG_DARK_CYAN);
	}

};

class PacManApp : public GameEngine::Application
{
public:

	PacManApp()
	{
		// Load all assets used and store them in a map
		GameEngine::Application::Get().m_Assets->AddSprite("Map", L"res/PacManMap.scene");

		PushLayer(new ExampleLayer());
		PushOverlay(new ExampleOverlay());
	}

	virtual ~PacManApp() = default;

};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new PacManApp();
}
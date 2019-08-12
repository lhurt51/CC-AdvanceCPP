#pragma once

#include <GameEngine.h>

// Project for acctually creating you game instance
class ExampleLayer : public GameEngine::Layer
{
public:

	ExampleLayer() : Layer("Example"),
		board(GameEngine::Application::Get().m_Assets->GetManager().AddEntity()),
		player(GameEngine::Application::Get().m_Assets->GetManager().AddEntity()),
		ai1(GameEngine::Application::Get().m_Assets->GetManager().AddEntity()),
		ai2(GameEngine::Application::Get().m_Assets->GetManager().AddEntity()),
		ai3(GameEngine::Application::Get().m_Assets->GetManager().AddEntity())
	{}

	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override
	{
		board.AddComponent<GameEngine::TransformComponent>();
		board.AddComponent<GameEngine::SpriteComponent>("Map");

		auto& spriteSize = board.GetComponent<GameEngine::SpriteComponent>().sprite.size;
		glm::vec2 newPos = { 80 - spriteSize.x * 0.5, 30 - spriteSize.y * 0.5 };
		board.GetComponent<GameEngine::TransformComponent>().position = newPos;
		GameEngine::SceneManager::LoadScene("Map", newPos);

		glm::vec2 playerPos = { 61, 25 };
		player.AddComponent<GameEngine::TransformComponent>(playerPos);
		player.AddComponent<GameEngine::SpriteComponent>("Player");
		player.AddComponent<GameEngine::KeyboardController>();
		player.GetComponent<GameEngine::SpriteComponent>().sprite.SetColor(0, 0, GameEngine::FG_YELLOW);
		player.AddComponent<GameEngine::ColliderComponent>("player");
		player.AddGroup(GameEngine::GroupPlayers);

		glm::vec2 enemyPos1 = { 76, 29 };
		ai1.AddComponent<GameEngine::TransformComponent>(enemyPos1);
		ai1.AddComponent<GameEngine::SpriteComponent>("Enemy");
		ai1.GetComponent<GameEngine::SpriteComponent>().sprite.SetColor(0, 0, GameEngine::FG_MAGENTA);
		ai1.AddComponent<GameEngine::ColliderComponent>("enemy");

		glm::vec2 enemyPos2 = { 79, 29 };
		ai2.AddComponent<GameEngine::TransformComponent>(enemyPos2);
		ai2.AddComponent<GameEngine::SpriteComponent>("Enemy");
		ai2.GetComponent<GameEngine::SpriteComponent>().sprite.SetColor(0, 0, GameEngine::FG_RED);
		ai2.AddComponent<GameEngine::ColliderComponent>("enemy");

		glm::vec2 enemyPos3 = { 82, 29 };
		ai3.AddComponent<GameEngine::TransformComponent>(enemyPos3);
		ai3.AddComponent<GameEngine::SpriteComponent>("Enemy");
		ai3.GetComponent<GameEngine::SpriteComponent>().sprite.SetColor(0, 0, GameEngine::FG_GREEN);
		ai3.AddComponent<GameEngine::ColliderComponent>("enemy");
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
		/*
		if (GameEngine::Input::IsKeyPressed(GE_KEY_A))
			m_Pos.x -= 10 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
			m_Pos.x += 10 * ts;

		if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
			m_Pos.y -= 10 * ts;
		else if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
			m_Pos.y += 10 * ts;
		*/

		auto& lastPlayerCol = player.GetComponent<GameEngine::ColliderComponent>();
		auto& colliders = GameEngine::Application::Get().m_Assets->GetManager().GetGroup(GameEngine::GroupColliders);

		for (auto& c : colliders)
		{
			GameEngine::ColliderComponent cCol = c->GetComponent<GameEngine::ColliderComponent>();

			if (GameEngine::Collision::AABB(cCol, lastPlayerCol))
			{
				player.GetComponent<GameEngine::TransformComponent>().position = lastPlayerPos;
			}
		}


		// GameEngine::RenderCommand::SetClearColor(GameEngine::BG_BLACK);
		GameEngine::RenderCommand::Clear();
		board.OnDraw();
		player.OnDraw();
		ai1.OnDraw();
		ai2.OnDraw();
		ai3.OnDraw();

		lastPlayerPos = player.GetComponent<GameEngine::TransformComponent>().position;
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
	GameEngine::Entity& player;
	GameEngine::Entity& ai1;
	GameEngine::Entity& ai2;
	GameEngine::Entity& ai3;

	glm::vec2 lastPlayerPos;

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
		GameEngine::Application::Get().m_Assets->AddSprite("Player", L"res/PacManSprite.sprite");
		GameEngine::Application::Get().m_Assets->AddSprite("Enemy", L"res/PacManEnemy.sprite");

		PushLayer(new ExampleLayer());
		PushOverlay(new ExampleOverlay());
	}

	virtual ~PacManApp() = default;

};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new PacManApp();
}
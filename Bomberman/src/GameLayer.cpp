#include "GameLayer.hpp"
#include "imgui.h"
#include "BombermanApp.hpp"
#include <gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

GameLayer::GameLayer()
	:m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.01f, 100.0f)
{
	m_Camera.SetRotation(glm::vec3(glm::radians(-60.0f), glm::radians(0.0f), 0));
	m_Camera.Recalculate();
	x = Swallow::AudioBuffer::Create("assets/Sounds/Background.wav");
	s = Swallow::AudioSource::Create();
	s->SetPosition({0.0f, 0.0f, 0.0f});
	s->SetVelocity({0.f, 0.f, 0.f});
	s->SetLooping(true);
	s->SetBuffer(x);
}

void GameLayer::OnAttach()
{
	s->Play();
	std::string path = "Saves/";
	std::ifstream in;
	in.open(path + m_Save + ".sav", std::ios::binary);
	if (m_Save.empty() || !in.good())
		m_Level = std::make_shared<Level>(map_size.x, map_size.y, chance);
	else
		m_Level = std::make_shared<Level>(m_Save);
}

void GameLayer::OnDetach()
{
	s->Stop();
	m_Level.reset();
}

void GameLayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(GameLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressed));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(GameLayer::OnWindowResize));
}

bool GameLayer::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool GameLayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	static_cast<void>(e);
	m_Camera.SetProjectionMatrix(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.01f, 100.0f);
	m_Camera.Recalculate();
	return false;
}

bool GameLayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool GameLayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_SPACE)
		m_Level->DropBomb(m_Level->GetPlayer()->Destination());
	else if (e.GetKeyCode() == SW_KEY_S && Swallow::Input::IsKeyPressed(SW_KEY_LEFT_SUPER))
		m_Level->Save(m_Save);
	else
		return false;
	return true;
}

void GameLayer::OnImGuiRender() {
}


void GameLayer::OnUpdate(Swallow::Timestep ts)
{
	static_cast<void>(ts);
	m_Position = m_Level->GetPlayer()->GetTransform()->GetPosition() + glm::vec3(0, 10, 6);
	m_Camera.SetPosition(m_Position);
	m_Camera.Recalculate();
	m_Level->Update(ts);

	Swallow::Renderer::BeginScene(m_Camera);

	m_Level->Draw();
	

	Swallow::Renderer::EndScene();
	if (m_Level->GetDeadStatus())
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadGame();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
	};
}
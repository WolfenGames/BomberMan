#include "GameLayer.hpp"
#include "imgui.h"
#include <gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

GameLayer::GameLayer()
	:m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.01f, 100.0f)
{
	m_Camera.SetRotation(glm::vec3(glm::radians(-60.0f), glm::radians(0.0f), 0));
	m_Camera.Recalculate();
}

void GameLayer::OnAttach()
{
	m_Level = std::make_shared<Level>(map_size.x, map_size.y);
}

void GameLayer::OnDetach()
{
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
}
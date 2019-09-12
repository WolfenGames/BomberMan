#include "swpch.hpp"
#include "Background.hpp"

#include "BackDrop.hpp"

#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

Background::Background(): m_Camera(-10, 10, -10, 10, 10, -10)
{
	m_BackDrop = std::make_shared<BackDrop>(glm::vec3(0,0,0));
	m_BackDrop->GetTransform()->SetScale({100.f, 1.f, 100.f,});
}

void Background::OnAttach(){}

void Background::OnDetach() {}

void Background::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(Background::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(Background::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(Background::OnKeyPressed));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(Background::OnWindowResize));
}

bool Background::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool Background::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool Background::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool Background::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	static_cast<void>(e);
	return false;
}

void Background::OnImGuiRender() {
}


void Background::OnUpdate(Swallow::Timestep ts)
{
	static_cast<void>(ts);
	Swallow::Renderer::BeginScene(m_Camera);
	Swallow::Renderer::Submit(m_BackDrop);
	Swallow::Renderer::EndScene();
}
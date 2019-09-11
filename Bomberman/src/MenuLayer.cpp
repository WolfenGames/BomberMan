#include "MenuLayer.hpp"
#include "imgui.h"
#include <gtc/type_ptr.hpp>
#include "gtx/transform.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"
#include "BombermanApp.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

MenuLayer::MenuLayer()
	:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Square = Swallow::Primatives::Quad();
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.2, 0.5, 0.9, 1.0));
	m_Square->SetMaterial(mat);
	m_Square->GetTransform()->SetPosition(glm::vec3(0.0f, 9.0f, 0.0f));
	m_Square->GetTransform()->Recalculate();
	chance = 0.6f;
	m_Text = Swallow::Text::Create();
	m_Text->SetColour({1.0f, 1.0f, 1.0f, 1.0f});
	m_Text->SetText("Welcome\nFriend");
	m_Text->Recalculate();

	x = Swallow::AudioBuffer::Create("assets/Sounds/Background.wav");
	s = Swallow::AudioSource::Create();
	s->SetPosition({0.0f, 0.0f, 0.0f});
	s->SetVelocity({0.f, 0.f, 0.f});
	s->SetLooping(true);
	s->Play(x);
}

void MenuLayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(MenuLayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(MenuLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(MenuLayer::OnKeyPressed));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(MenuLayer::OnWindowResize));
}

bool MenuLayer::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool MenuLayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	static_cast<void>(e);
	m_Camera.SetProjectionMatrix(-10, 10, -10, 10, 10, -10);
	m_Camera.Recalculate();
	return false;
}

bool MenuLayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool MenuLayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		Swallow::Application::Get().End();
	}
	else if (e.GetKeyCode() == SW_KEY_SPACE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
	}
	else
		return false;
	return true;
}

void MenuLayer::OnImGuiRender() {
	ImGui::Begin("Menu");
	ImGui::SliderInt2("Level Size", glm::value_ptr(map_size), 1, 50);
	ImGui::SliderFloat("GenPercent", &chance, 0.1, 1, "%.1f", 1.0f);
	ImGui::End();
}


void MenuLayer::OnUpdate(Swallow::Timestep ts)
{
	static_cast<void>(ts);
	Swallow::Renderer::BeginScene(m_Camera);

	Swallow::Renderer::Submit(m_Square);
	Swallow::Renderer::Submit(m_Text);

	Swallow::Renderer::EndScene();
}
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

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Quit", 7.0f, 4.0f);
	m_Menu->AddButton("Play", 7.0f, 7.1f);
	m_Menu->AddButton("Click here to get fucked", -4.0f, 1.0f);
	m_Menu->GetButtons().back()->GetBackground()->GetTransform()->SetScale(glm::vec3(6.0f, 1.5f, 1.0f));
	m_Menu->GetButtons().back()->GetBackground()->GetTransform()->SetPosition(glm::vec3(-4.0f + 5.8f, 1.0f + 0.5f, 0.9f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
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
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	SW_CORE_INFO("Mouse click X: {}", x);
	SW_CORE_INFO("Mouse click Y: {}\n", y);
	if (x > 0.7f && x < 1.0f)
		Swallow::Application::Get().End();


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

	Swallow::Renderer::Submit(m_Menu->GetBackground());
	Swallow::Renderer::Submit(m_Menu->GetText());
	for (auto a : m_Menu->GetButtons())
	{
		Swallow::Renderer::Submit(a->GetBackground());
		Swallow::Renderer::Submit(a->GetText());
	}
	Swallow::Renderer::EndScene();
}
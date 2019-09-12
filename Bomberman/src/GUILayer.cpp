#include "GUILayer.hpp"
#include "imgui.h"
#include <gtc/type_ptr.hpp>
#include "gtx/transform.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"
#include "BombermanApp.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

GUILayer::GUILayer()
	:m_Camera(-10, 10, -10, 10, 10, -10)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();
	
	m_PinkThing = Swallow::Primatives::Quad();
	Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.9, 0.2, 0.7, 1.0));
	m_PinkThing->SetMaterial(mat);
	m_PinkThing->GetTransform()->SetPosition(glm::vec3(0.0f, 9.0f, 0.0f));
	m_PinkThing->GetTransform()->Recalculate();
	m_Info = Swallow::Text::Create();
	m_Info->SetColour({1.0f, 1.0f, 1.0f, 1.0f});
	m_Info->SetText(m_InfoVal);
	m_Info->Recalculate();
	m_Info->GetTransform()->SetPosition({-10, 9, 0});
}

void GUILayer::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(GUILayer::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(GUILayer::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(GUILayer::OnKeyPressed));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(GUILayer::OnWindowResize));
}

bool GUILayer::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool GUILayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	static_cast<void>(e);
	m_Camera.SetProjectionMatrix(-10, 10, -10, 10, 10, -10);
	m_Camera.Recalculate();
	return false;
}

bool GUILayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	return false;
}

bool GUILayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadGame();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
	}
	else
		return false;
	return true;
}

void GUILayer::OnImGuiRender() {
}


void GUILayer::OnUpdate(Swallow::Timestep ts)
{
	static_cast<void>(ts);
	Swallow::Renderer::BeginScene(m_Camera);

	Swallow::Renderer::Submit(m_PinkThing);
	m_Info->SetText(m_InfoVal);
	m_Info->Recalculate();
	Swallow::Renderer::Submit(m_Info);
	Swallow::Renderer::EndScene();
}
#include "GUILayer.hpp"
#include "imgui.h"
#include <gtc/type_ptr.hpp>
#include "gtx/transform.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

GUILayer::GUILayer()
	:m_Camera(-10, 10, -10, 10, 10, -10)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();
	m_Square = Swallow::VertexArray::Create();
	
	float squareBuffer[4 * 9] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 
		1.0f,-1.0f, 0.0f, 
		-1.0f,-1.0f, 0.0f
	};

	Swallow::Ref<Swallow::VertexBuffer> squareVB;
	squareVB = Swallow::VertexBuffer::Create(squareBuffer, sizeof(squareBuffer));

	squareVB->SetLayout({
		{ Swallow::ShaderDataType::Float3, "a_Position" }
	});

	m_Square->AddVertexBuffer(squareVB);

	uint32_t squareIndex[3 * 2] = {
		0, 1, 2,
		2, 3, 0
	};

	Swallow::Ref<Swallow::IndexBuffer> squareIB;
	squareIB = Swallow::IndexBuffer::Create(squareIndex, sizeof(squareIndex) / sizeof(uint32_t));
	m_Square->SetIndexBuffer(squareIB);

	std::string sVertexSrc = R"(
		#version 330 core
		

		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;

		void main() {
			gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
		}
	)";

	std::string sFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		uniform vec3 u_Color;

		void main() {
			color = vec4(u_Color, 1);
		}
	)";

	m_Shader = Swallow::Shader::Create(sVertexSrc, sFragmentSrc);
	Swallow::RenderCommand::SetDepthTest(true);
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
	return true;
}

bool GUILayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	m_Camera.SetProjectionMatrix(-10, 10, -10, 10, 10, -10);
	m_Camera.Recalculate();
	return true;
}

bool GUILayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	return true;
}

bool GUILayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
		Swallow::Application::Get().End();
	return true;
}

void GUILayer::OnImGuiRender() {
}


void GUILayer::OnUpdate(Swallow::Timestep ts)
{
	Swallow::Renderer::BeginScene(m_Camera);

	m_Shader->Bind();

	glm::vec3 pos(0.0f, 9.0f, 0.0f);
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.2, 0.5, 0.9));
	Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Square,
		glm::translate(pos) * glm::scale(glm::vec3(1)));

	Swallow::Renderer::EndScene();
}
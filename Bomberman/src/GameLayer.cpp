#include "GameLayer.hpp"
#include "imgui.h"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.hpp"

GameLayer::GameLayer()
	:m_Camera(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f)
{
	m_Camera.SetPosition(glm::vec3(5, 20, 15));
	m_Camera.SetRotation(glm::vec3(glm::radians(-45.0f), glm::radians(0.0f), 0));
	m_Camera.Recalculate();
	m_Cube = Swallow::VertexArray::Create();
	
	float squareBuffer[8 * 9] = {
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 
		1.0f,-1.0f, 1.0f, 
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f,-1.0f, -1.0f,
		-1.0f,-1.0f, -1.0f
	};

	Swallow::Ref<Swallow::VertexBuffer> squareVB;
	squareVB = Swallow::VertexBuffer::Create(squareBuffer, sizeof(squareBuffer));

	squareVB->SetLayout({
		{ Swallow::ShaderDataType::Float3, "a_Position" }
	});

	m_Cube->AddVertexBuffer(squareVB);

	uint32_t squareIndex[3 * 12] = {
		//North 0 1 2 3
		0, 1, 2,
		2, 3, 0,
		//East 1 5 6 2
		1, 5, 6,
		6, 2, 1,
		//South 7 6 5 4
		7, 6, 5,
		5, 4, 7,
		//West 0 3 7 4
		0, 3, 7,
		7, 4, 0,
		//Top 0 4 5 1
		0, 4, 5,
		5, 1, 0,
		//Bottom 7 3 2 6
		7, 3, 2,
		2, 6, 7
	};

	Swallow::Ref<Swallow::IndexBuffer> squareIB;
	squareIB = Swallow::IndexBuffer::Create(squareIndex, sizeof(squareIndex) / sizeof(uint32_t));
	m_Cube->SetIndexBuffer(squareIB);

	std::string sVertexSrc = R"(
		#version 330 core
		

		layout(location = 0) in vec3 a_Position;

		out vec3 v_Normal;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Model;
		uniform mat4 u_Rot;

		void main() {
			v_Normal = normalize(u_Rot * vec4(a_Position, 0.0)).xyz;
			gl_Position = (u_ViewProjection * u_Model) * vec4(a_Position, 1.0);
		}
	)";

	std::string sFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;

		uniform vec3 u_Color;
		in vec3 v_Normal;
		uniform vec3 u_LightDirection = vec3(0, -1, 0);

		void main() {
			float Light = max(0.0, dot(v_Normal, -normalize(u_LightDirection))) * 0.95 + 0.05;
			color = vec4(u_Color * Light, 1);
		}
	)";

	m_Shader = Swallow::Shader::Create(sVertexSrc, sFragmentSrc);
	Swallow::RenderCommand::SetDepthTest(true);
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
	return true;
}

bool GameLayer::OnWindowResize(Swallow::WindowResizeEvent &e)
{
	m_Camera.SetProjectionMatrix(glm::radians(60.0f), Swallow::Application::Get().GetWindow().GetWidth() / (float)Swallow::Application::Get().GetWindow().GetHeight(), 0.0001f, 100000.0f);
	m_Camera.Recalculate();
	return true;
}

bool GameLayer::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	return true;
}

bool GameLayer::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
		Swallow::Application::Get().End();
	return true;
}

void GameLayer::OnImGuiRender() {
}


void GameLayer::OnUpdate(Swallow::Timestep ts)
{
	Swallow::Renderer::BeginScene(m_Camera);

	m_Shader->Bind();

	static float rot = 0.0f;
	static float axis = 0.0f;
	rot += ts.GetSeconds() * 2.5;
	axis += ts.GetSeconds() * 2.5;
	if (axis > 10)
		axis = -10;
	for (int z = 0; z < 10; z++)
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
			{
				std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
				std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformMat4("u_Rot", glm::rotate(glm::radians(rot), glm::vec3((axis - x) / 10.0, (axis - y) / 10.0, (axis - z) / 10.0)) * glm::rotate(glm::radians(rot), glm::vec3(x / 10.0, y / 10.0, z / 10.0)));
				std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(x / 10.0, y / 10.0, z / 10.0));
				Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Cube,
				glm::rotate(glm::radians(rot), glm::vec3((axis - x) / 10.0, (axis - y) / 10.0, (axis - z) / 10.0)) *
				glm::translate(glm::normalize(glm::vec3(x - 4.5, y - 4.5, z - 4.5)) * glm::max<float>(glm::max<float>(glm::abs(x - 4.5), glm::abs(y - 4.5)), glm::abs(z - 4.5))) *
				glm::rotate(glm::radians(rot), glm::vec3(x / 10.0, y / 10.0, z / 10.0)) *
				glm::scale(glm::vec3(0.3)));
			}

	Swallow::Renderer::EndScene();
}
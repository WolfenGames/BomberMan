#include "Player.hpp"
#include "gtx/transform.hpp"

Player::Player(const glm::vec3 &Pos)
	:m_Positition(Pos)
{
}

Player::~Player()
{
}

void Player::Update(Swallow::Timestep ts)
{
	if (Swallow::Input::IsKeyPressed(SW_KEY_W))
		m_Positition.z += ts.GetSeconds() * -5;
	if (Swallow::Input::IsKeyPressed(SW_KEY_A))
		m_Positition.x += ts.GetSeconds() * -5;
	if (Swallow::Input::IsKeyPressed(SW_KEY_S))
		m_Positition.z += ts.GetSeconds() * 5;
	if (Swallow::Input::IsKeyPressed(SW_KEY_D))
		m_Positition.x += ts.GetSeconds() * 5;
}

void Player::Draw()
{
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.2, 0.5, 0.9));
	Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Cube,
		glm::translate(m_Positition) * glm::scale(glm::vec3(0.8)));
}

void Player::SetModels(Swallow::Ref<Swallow::VertexArray>& VA, Swallow::Ref<Swallow::Shader>& Shader)
{
	m_Cube = VA;
	m_Shader = Shader;
}

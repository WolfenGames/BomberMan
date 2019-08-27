#include "Player.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"

Player::Player(const glm::vec3 &Pos, Level &l)
	:m_Position(Pos), m_Level(l), m_Destination(m_Position)
{
}

Player::~Player()
{
}

void Player::Update(Swallow::Timestep ts)
{
	static float threshold = 0.1f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_W)
		&& glm::abs(m_Destination.x - m_Position.x) < threshold && m_Level.IsEmpty(m_Position + glm::vec3(0.0f, 0.0f, -1.0f)))
		m_Destination.z = glm::floor(m_Position.z + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_S)
		&& glm::abs(m_Destination.x - m_Position.x) < threshold && m_Level.IsEmpty(m_Position + glm::vec3(0.0f, 0.0f, 1.0f)))
		m_Destination.z = glm::floor(m_Position.z - 0.5f + threshold) + 1.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_A)
		&& glm::abs(m_Destination.z - m_Position.z) < threshold && m_Level.IsEmpty(m_Position + glm::vec3(-1.0f, 0.0f, 0.0f)))
		m_Destination.x = glm::floor(m_Position.x + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_D)
		&& glm::abs(m_Destination.z - m_Position.z) < threshold && m_Level.IsEmpty(m_Position + glm::vec3(1.0f, 0.0f, 0.0f)))
		m_Destination.x = glm::floor(m_Position.x - 0.5f + threshold) + 1.5f;
	if (glm::length(m_Destination - m_Position) > 0.01f)
		m_Position += glm::normalize(m_Destination - m_Position) * ts.GetSeconds() * 2.0f;
}

void Player::Draw()
{
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", glm::vec3(0.2, 0.5, 0.9));
	Swallow::Renderer::Submit(std::dynamic_pointer_cast<Swallow::OpenGLShader>(m_Shader), m_Cube,
		glm::translate(m_Position) * glm::scale(glm::vec3(0.8f)));
}

void Player::SetModels(Swallow::Ref<Swallow::VertexArray>& VA, Swallow::Ref<Swallow::Shader>& Shader)
{
	m_Cube = VA;
	m_Shader = Shader;
}

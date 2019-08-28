#include "Player.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"

Player::Player(const glm::vec3 &Pos, Level &l)
	:m_Level(l)
{
	GetTransform()->SetPosition(Pos);
	m_Destination = GetTransform()->GetPosition();
}

Player::~Player()
{
}

void Player::Update(Swallow::Timestep ts)
{
	static float threshold = 0.1f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_W)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f)))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_S)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f)))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z - 0.5f + threshold) + 1.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_A)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f)))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_D)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f)))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x - 0.5f + threshold) + 1.5f;
	if (glm::length(m_Destination - GetTransform()->GetPosition()) > 0.01f)
		GetTransform()->GetPosition() += glm::normalize(m_Destination - GetTransform()->GetPosition()) * ts.GetSeconds() * 2.0f;
	GetTransform()->Recalculate();
}

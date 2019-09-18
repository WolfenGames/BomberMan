#include "Player.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Player::Player(const glm::vec3 &Pos, Level &l)
	:m_Level(l), m_FireDistance(2), m_BombCount(2)
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	SetMaterial(mat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman"));
	GetTransform()->SetScale(glm::vec3(0.20f));
	GetTransform()->SetPosition(Pos);
	m_Destination = GetTransform()->GetPosition();
	#ifdef SW_DEBUG
		m_Ghost = true;
	#endif
}

Player::~Player()
{
}

bool Player::AddPower(Swallow::Ref<PowerUp> power)
{
	switch (power->getPowerUpType())
	{
		case PowerUpTypes::eFireIncrease:
			m_FireDistance++;
			m_FireDistance = std::clamp(m_FireDistance, 2, 7);
			return true;
		case PowerUpTypes::eFireDecrease:
			m_FireDistance--;
			m_FireDistance = std::clamp(m_FireDistance, 2, 7);
			return true;
		case PowerUpTypes::eBombUp:
			m_BombCount++;
			m_BombCount = std::clamp(m_BombCount, 1, ~(1 << 31));
			return true;
		case PowerUpTypes::eBombDown:
			m_BombCount--;
			m_BombCount = std::clamp(m_BombCount, 1, ~(1 << 31));
			return true;
		case PowerUpTypes::eBombsCanBypassWalls:
			m_BombsCanBypassWalls = true;
			return true;
		case PowerUpTypes::eSoftBlockPass:
		#ifndef	SW_DEBUG
			m_Ghost = !m_Ghost;
		#endif
			return true;
		case PowerUpTypes::eKey:
			m_HasKey = true;
			return true;
		case PowerUpTypes::eExit:
			if (m_HasKey && m_Level.NoEnemies())
			{
				SW_TRACE("You Win!");
				return true;
			}
		default:
			return false;
	}
	return false;
}

void Player::Update(Swallow::Timestep ts)
{
	static float threshold = 0.1f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_W)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f), Ghost())))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_S)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f), Ghost())))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z - 0.5f + threshold) + 1.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_A)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), Ghost())))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_D)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f), Ghost())))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x - 0.5f + threshold) + 1.5f;
	float len = glm::length(m_Destination - GetTransform()->GetPosition());
	if (len > 0.01f)
		GetTransform()->GetPosition() += glm::normalize(m_Destination - GetTransform()->GetPosition()) * glm::min(ts.GetSeconds() * 2.0f, len);
	GetTransform()->Recalculate();
}

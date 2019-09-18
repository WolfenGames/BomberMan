#include "Player.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Player::Player(const glm::vec3 &Pos, Level &l)
	:m_Level(l), m_FireDistance(4), m_BombCount(3)
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	SetMaterial(mat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman"));
	GetTransform()->SetScale(glm::vec3(0.20f));
	GetTransform()->SetPosition(Pos);
	m_Destination = GetTransform()->GetPosition();
	// for(int i = 0; i < 12; i++)
	// 	AddPower(std::make_shared<FireIncrease>());
	// AddPower(std::make_shared<BombsCanBypassWalls>());
	// AddPower(std::make_shared<SoftBlockPass>());
}

Player::~Player()
{
}

void Player::AddPower(Swallow::Ref<PowerUp> power)
{
	power->OnAdd(this);
	m_PowerUps.push_back(power);
}

void Player::Update(Swallow::Timestep ts)
{
	static float threshold = 0.1f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_W)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f))))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_S)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f))))
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z - 0.5f + threshold) + 1.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_A)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f))))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x + 0.5f - threshold) - 0.5f;
	if (Swallow::Input::IsKeyPressed(SW_KEY_D)
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level.IsExit(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.f)) || m_Level.IsEmpty(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f))))
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x - 0.5f + threshold) + 1.5f;
	float len = glm::length(m_Destination - GetTransform()->GetPosition());
	if (len > 0.01f)
		GetTransform()->GetPosition() += glm::normalize(m_Destination - GetTransform()->GetPosition()) * glm::min(ts.GetSeconds() * 2.0f, len);
	GetTransform()->Recalculate();

	for(auto p: m_PowerUps)
	{
		p->OnUpdate(ts);
		if (p->CanDelete())
			p->OnRemove(this);
	}
	m_PowerUps.remove_if([](Swallow::Ref<PowerUp> p){ return p->CanDelete(); });
}

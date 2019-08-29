#include "Enemy.hpp"

Enemy::Enemy(const glm::vec3& pos, Level& level): m_Level(level)
{
	GetTransform()->SetPosition(pos);
	m_Pos = GetTransform()->GetPosition();
	m_MoveDir = { 0, 0 };
}

void Enemy::makeDecision()
{
	//TODO: Make Decision;
	glm::vec2	newDir = { 0, 0 };
	newDir.x = (rand() % 2) - 1;
	newDir.y = (rand() % 2) - 1;
	m_MoveDir = newDir;
	m_MaxMoves = rand() % 10;
}

glm::vec3& Enemy::Destination()
{
	return m_Pos;
}

void Enemy::Update(Swallow::Timestep ts)
{
	static float threshold = 0.1f;

	if (m_MaxMoves <= 0)
		this->makeDecision();

	if ((m_MoveDir.x == 1 && m_MoveDir.y == 1) || (m_MoveDir.x == 0 && m_MoveDir.y == 0))
		m_MaxMoves = 0;
	if (m_MoveDir.x == 1 && m_MoveDir.y == 0)
		m_Pos.z = glm::floor(GetTransform()->GetPosition().z + 1.f - threshold) - 1.f;
	if (m_MoveDir.x == -1 && m_MoveDir.y == 0)
		m_Pos.z = glm::floor(GetTransform()->GetPosition().z -1.f - threshold) - 1.f;
	if (m_MoveDir.x == -1 && m_MoveDir.y == 0)
		m_Pos.x = glm::floor(GetTransform()->GetPosition().x + 1.f - threshold) - 1.f;
	if (m_MoveDir.x == 0 && m_MoveDir.y == -1)
		m_Pos.x = glm::floor(GetTransform()->GetPosition().x - 1.f - threshold) - 1.f;


	if (m_MaxMoves > 0)
	{
		float len = glm::length(m_Pos - GetTransform()->GetPosition());
		if (len > 0.01f)
			GetTransform()->GetPosition() += glm::normalize(m_Pos - GetTransform()->GetPosition()) * glm::min(ts.GetSeconds() * 2.0f, len);
		GetTransform()->Recalculate();
	}
}

Enemy::~Enemy()
{
}


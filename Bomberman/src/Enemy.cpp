#include "Enemy.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"
#include "gtc/random.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

Enemy::Enemy(const glm::vec3& pos, Swallow::Ref<Level> level)
{
	m_Level = level;

	GetTransform()->SetPosition(pos);
	m_Destination = GetTransform()->GetPosition();
	m_MoveDir = { 1.0f, 0.0, 0.0 };
	//SetVertexArray(Swallow::AssetManager::FetchObject("Enemy", "Bomberman00"));
	
	//Supports animations
	//animMaterial = Swallow::AnimationMaterial::Create();
	//animMaterial->SetColour(glm::vec4(0.9f, 0.1f, 0.2f, 1.0f));
	//SetMaterial(animMaterial);
	//old materials
	//static Swallow::Ref<Swallow::FlatColourMaterialInstance> mat2 = Swallow::FlatColourMaterial::Create();
	//mat2->SetColour(glm::vec4(0.9f, 0.1f, 0.2f, 1.0f));
	//SetMaterial(mat2);
	//GetTransform()->SetScale(glm::vec3(1.0f));

	m_EnemyAnimMaterial = Swallow::AnimationMaterial::Create();
	m_EnemyAnimMaterial->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(m_EnemyAnimMaterial);

	SetVertexArray(Swallow::VertexArray::Create());
	GetVertexArray()->SetIndexBuffer(Swallow::AssetManager::FetchObject("Enemy", "Enemy02")->GetIndexBuffer());

	m_EnemyWalkAnimation = Swallow::AnimationController::Create("Enemy");

	m_EnemyWalkAnimation->AddKeyFrame("Enemy00");
	m_EnemyWalkAnimation->AddKeyFrame("Enemy01");
	m_EnemyWalkAnimation->AddKeyFrame("Enemy02");
	m_EnemyWalkAnimation->AddKeyFrame("Enemy03");


	m_EnemyWalkAnimation->SetAdvanceTimer(0.0f);
	GetVertexArray()->AddVertexBuffer(m_EnemyWalkAnimation->GetVertexBuffer1());
	GetVertexArray()->AddVertexBuffer(m_EnemyWalkAnimation->GetVertexBuffer2());

	makeDecision();
}

void Enemy::makeDecision()
{
	//TODO: Make Decision;
	int dir = glm::linearRand(0, 3);
	switch (dir)
	{
		case 0:
			m_MoveDir = {1.0, 0.0, 0.0};
			break;
		case 1:
			m_MoveDir = {-1.0, 0.0, 0.0};
			break;
		case 2:
			m_MoveDir = {0.0, 0.0, 1.0};
			break;
		case 3:
			m_MoveDir = {0.0, 0.0, -1.0};
			break;
	}

}

glm::vec3& Enemy::Destination()
{
	return m_Destination;
}

void Enemy::Update(Swallow::Timestep ts)
{
	switch (m_EnemyWalkAnimation->Advance(ts.GetSeconds() * 4.f))
	{
		case ONGOING_KEYFRAME:
			break;
		case LAST_KEYFRAME:
			m_EnemyWalkAnimation->SetAdvanceTimer(0.0f);
		case NEXT_KEYFRAME:
			GetVertexArray()->GetVertexBuffers().clear();
			GetVertexArray()->AddVertexBuffer(m_EnemyWalkAnimation->GetVertexBuffer1());
			GetVertexArray()->AddVertexBuffer(m_EnemyWalkAnimation->GetVertexBuffer2());
			break;
	}
	m_EnemyAnimMaterial->SetAnim(glm::vec1(m_EnemyWalkAnimation->GetAdvancedTime()));

	static float threshold = 0.1f;
	if (m_MoveDir.z == -1
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f), false)))
	{
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z + 0.5f - threshold) - 0.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (m_MoveDir.z == 1
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f), false)))
	{
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z - 0.5f + threshold) + 1.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	}
	if (m_MoveDir.x == -1
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), false)))
	{
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x + 0.5f - threshold) - 0.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	}
	if (m_MoveDir.x == 1
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f), false)))
	{
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x - 0.5f + threshold) + 1.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}
	float len = glm::length(m_Destination - GetTransform()->GetPosition());
	if (len > 0.1f)
	{
		GetTransform()->GetPosition() += glm::normalize(m_Destination - GetTransform()->GetPosition()) * glm::min(ts.GetSeconds() * 2.0f, len);
	}
	else
		makeDecision();
	GetTransform()->Recalculate();
}

Enemy::~Enemy()
{
}


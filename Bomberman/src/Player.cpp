#include "Player.hpp"
#include "Level.hpp"
#include "gtx/transform.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include "BombermanApp.hpp"

Player::Player()
{
	//Old material
	//static Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	//mat->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	//SetMaterial(mat);
	
	//New material with aniamtions
	
	animMaterial = Swallow::AnimationMaterial::Create();
	//animMaterial->SetColour(glm::vec4(0.2f, 0.5f, 1.0f, 1.0f));
	animMaterial->SetTexture(Swallow::AssetManager::FetchTexture("BomberManColor"));
	SetMaterial(animMaterial);
	//SetVertexArray(Swallow::VertexArray::Create());
	
	SetVertexArray(Swallow::VertexArray::Create());
	GetVertexArray()->SetIndexBuffer(Swallow::AssetManager::FetchObject("BombermanIdle", "BombermanIdle00")->GetIndexBuffer());

	m_WalkAnimation = Swallow::AnimationController::Create("Bomberman");

	m_WalkAnimation->AddKeyFrame("Bomberman00");
	m_WalkAnimation->AddKeyFrame("Bomberman01");
	m_WalkAnimation->AddKeyFrame("Bomberman02");
	m_WalkAnimation->AddKeyFrame("Bomberman03");
	m_WalkAnimation->AddKeyFrame("Bomberman04");
	m_WalkAnimation->AddKeyFrame("Bomberman05");
	m_WalkAnimation->AddKeyFrame("Bomberman06");
	m_WalkAnimation->AddKeyFrame("Bomberman07");

	m_WalkAnimation->SetAdvanceTimer(0.0f);


	m_IdleAnimation = Swallow::AnimationController::Create("BombermanIdle");

	m_IdleAnimation->AddKeyFrame("BombermanIdle00");
	m_IdleAnimation->AddKeyFrame("BombermanIdle01");
	m_IdleAnimation->AddKeyFrame("BombermanIdle02");
	m_IdleAnimation->AddKeyFrame("BombermanIdle03");
	m_IdleAnimation->AddKeyFrame("BombermanIdle04");
	m_IdleAnimation->AddKeyFrame("BombermanIdle05");
	m_IdleAnimation->AddKeyFrame("BombermanIdle06");
	
	m_IdleAnimation->SetAdvanceTimer(0.0f);
	
	GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer1());
	GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer2());

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
		case PowerUpTypes::eSpeedUp:
			m_Speed += 0.25f;
			m_Speed = glm::clamp(m_Speed, 1.0f, 6.0f);
			return true;
		case PowerUpTypes::eSpeedDown:
			m_Speed -= 0.25f;
			m_Speed = glm::clamp(m_Speed, 1.0f, 6.0f);
			return true;
		case PowerUpTypes::eBombsCanBypassWalls:
			m_BombsCanBypassWalls = true;
			return true;
		case PowerUpTypes::eSoftBlockPass:
			m_Ghost = !m_Ghost;
			return true;
		case PowerUpTypes::eKey:
			m_HasKey = true;
			return true;
		case PowerUpTypes::eExit:
			if (m_HasKey && m_Level->NoEnemies())
			{
				m_Won = true;
				return true;
			}
		default:
			return false;
	}
	return false;
}

void Player::Update(Swallow::Timestep ts)
{
	bool isRunning = false;
	static float threshold = 0.1f;

	if (Swallow::Input::IsKeyPressed(SW_KEY_W)
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, -1.0f), Ghost())))
	{
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z + 0.5f - threshold) - 0.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
	}
	if (Swallow::Input::IsKeyPressed(s->GetKeybindings()["Down"])
		&& glm::abs(m_Destination.x - GetTransform()->GetPosition().x) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 1.0f), Ghost())))
	{
		m_Destination.z = glm::floor(GetTransform()->GetPosition().z - 0.5f + threshold) + 1.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, glm::radians(270.0f), 0.0f));
	}
	if (Swallow::Input::IsKeyPressed(s->GetKeybindings()["Left"])
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), Ghost())))
	{
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x + 0.5f - threshold) - 0.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, glm::radians(180.0f), 0.0f));
	}
	if (Swallow::Input::IsKeyPressed(s->GetKeybindings()["Right"])
		&& glm::abs(m_Destination.z - GetTransform()->GetPosition().z) < threshold && (m_Level->IsEmpty(GetTransform()->GetPosition() + glm::vec3(1.0f, 0.0f, 0.0f), Ghost())))
	{
		m_Destination.x = glm::floor(GetTransform()->GetPosition().x - 0.5f + threshold) + 1.5f;
		GetTransform()->SetRotation(glm::vec3(0.0f, glm::radians(0.0f), 0.0f));
	}
	float len = glm::length(m_Destination - GetTransform()->GetPosition());
	if (len > 0.01f)
	{
		GetTransform()->GetPosition() += glm::normalize(m_Destination - GetTransform()->GetPosition()) * glm::min(ts.GetSeconds() * m_Speed, len);
		isRunning = true;
	}
	GetTransform()->Recalculate();

	if (isRunning)
	{
		GetVertexArray()->SetIndexBuffer(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman00")->GetIndexBuffer());

		GetVertexArray()->GetVertexBuffers().clear();
		GetVertexArray()->AddVertexBuffer(m_WalkAnimation->GetVertexBuffer1());
		GetVertexArray()->AddVertexBuffer(m_WalkAnimation->GetVertexBuffer2());

		switch (m_WalkAnimation->Advance(ts.GetSeconds() * 5.5f * m_Speed))
		{			case ONGOING_KEYFRAME:
				break;
			case LAST_KEYFRAME:
				m_WalkAnimation->SetAdvanceTimer(0.0f);
			case NEXT_KEYFRAME:
				GetVertexArray()->GetVertexBuffers().clear();
				GetVertexArray()->AddVertexBuffer(m_WalkAnimation->GetVertexBuffer1());
				GetVertexArray()->AddVertexBuffer(m_WalkAnimation->GetVertexBuffer2());
				break;
		}
		m_IdleAnimation->SetAdvanceTimer(0.0f);
		animMaterial->SetAnim(glm::vec1(m_WalkAnimation->GetAdvancedTime()));
	}
	else
	{
		GetVertexArray()->SetIndexBuffer(Swallow::AssetManager::FetchObject("BombermanIdle", "BombermanIdle00")->GetIndexBuffer());

		GetVertexArray()->GetVertexBuffers().clear();
		GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer1());
		GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer2());

		switch (m_IdleAnimation->Advance(ts.GetSeconds() * 0.5f * m_Speed))
		{
			case ONGOING_KEYFRAME:
				break;
			case LAST_KEYFRAME:
				m_IdleAnimation->SetAdvanceTimer(0.0f);
			case NEXT_KEYFRAME:
				GetVertexArray()->GetVertexBuffers().clear();
				GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer1());
				GetVertexArray()->AddVertexBuffer(m_IdleAnimation->GetVertexBuffer2());
				break;
		}
		m_WalkAnimation->SetAdvanceTimer(0.0f); 
		animMaterial->SetAnim(glm::vec1(m_IdleAnimation->GetAdvancedTime()));
	}
	
}

#include "swpch.hpp"
#include "PowerUp.hpp"
#include "Player.hpp"
#include <Swallow.hpp>
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

FireIncrease::FireIncrease(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> FireIncreaseMat = Swallow::FlatColourMaterial::Create();
	FireIncreaseMat->SetColour(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));
	SetMaterial(FireIncreaseMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
}

void	FireIncrease::OnAdd(Player* player)
{
	player->SetIncreaseFireDistance(this->range);
}

void	FireIncrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	FireIncrease::OnRemove(Player* player)
{
	player->SetDecreaseFireDistance(this->range);
}

bool	FireIncrease::CanDelete()
{
	return m_Delete;
}

FireDecrease::FireDecrease(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> FireDecreaseMat = Swallow::FlatColourMaterial::Create();
	FireDecreaseMat->SetColour(glm::vec4(0.4f, 0.5f, 0.3f, 1.f));
	SetMaterial(FireDecreaseMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
};

void	FireDecrease::OnAdd(Player* player)
{
	player->SetDecreaseFireDistance(this->range);
}

void	FireDecrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	FireDecrease::OnRemove(Player* player)
{
	player->SetIncreaseFireDistance(this->range);
}

bool FireDecrease::CanDelete()
{
	return m_Delete;
}

BombUp::BombUp(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombUpMat = Swallow::FlatColourMaterial::Create();
	BombUpMat->SetColour(glm::vec4(0.5f, 0.4f, 0.2f, 1.f));
	SetMaterial(BombUpMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
};

void	BombUp::OnAdd(Player* player)
{
	player->SetIncreaseBombCount(this->increase);
}

void	BombUp::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void	BombUp::OnRemove(Player* player)
{
	player->SetDecreaseBombCount(this->increase);
}

bool	BombUp::CanDelete()
{
	return m_Delete;
}

BombDown::BombDown(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombDownMat = Swallow::FlatColourMaterial::Create();
	BombDownMat->SetColour(glm::vec4(0.6f, 0.3f, 0.2f, 1.f));
	SetMaterial(BombDownMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
};

void	BombDown::OnAdd(Player* player)
{
	player->SetDecreaseBombCount(this->decrease);
}

void BombDown::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void BombDown::OnRemove(Player* player)
{
	player->SetIncreaseBombCount(this->decrease);
}

bool	BombDown::CanDelete()
{
	return m_Delete;
}

BombsCanBypassWalls::BombsCanBypassWalls(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombsCanBypassWallsMat = Swallow::FlatColourMaterial::Create();
	BombsCanBypassWallsMat->SetColour(glm::vec4(0.8f, 0.1f, 0.7f, 1.f));
	SetMaterial(BombsCanBypassWallsMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
};

void	BombsCanBypassWalls::OnAdd(Player* player)
{
	player->SetBombsCanBypassWalls(true);
}

void BombsCanBypassWalls::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void BombsCanBypassWalls::OnRemove(Player* player)
{
	player->SetBombsCanBypassWalls(false);
}

bool	BombsCanBypassWalls::CanDelete()
{
	return m_Delete;
}

SoftBlockPass::SoftBlockPass(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SoftBlockPassMat = Swallow::FlatColourMaterial::Create();
	SoftBlockPassMat->SetColour(glm::vec4(0.f, 0.f, 1.f, 1.f));
	SetMaterial(SoftBlockPassMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
};
void	SoftBlockPass::OnAdd(Player* player)
{
	player->SetGhost(true);
}

void SoftBlockPass::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetMiliseconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

void SoftBlockPass::OnRemove(Player* player)
{
	player->SetGhost(false);
}

bool	SoftBlockPass::CanDelete()
{
	return m_Delete;
}

PowerUpFactory::PowerUpFactory(){}

Swallow::Ref<PowerUp>	PowerUpFactory::newPowerUp(PowerUpTypes type)
{
	switch (type)
	{
	case PowerUpTypes::eFireIncrease:
		return std::make_shared<FireIncrease>();
	case PowerUpTypes::eFireDecrease:
		return std::make_shared<FireDecrease>();
	case PowerUpTypes::eBombUp:
		return std::make_shared<BombUp>();
	case PowerUpTypes::eBombDown:
		return std::make_shared<BombDown>();
	case PowerUpTypes::eBombsCanBypassWalls:
		return std::make_shared<BombsCanBypassWalls>();
	
	default:
		return nullptr;
	}
}
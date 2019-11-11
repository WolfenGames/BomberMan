#include "swpch.hpp"
#include "PowerUp.hpp"
#include "Player.hpp"
#include <Swallow.hpp>
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include "Swallow/Renderer/texture/TextureMaterial.hpp"


#pragma region FireIncrease
FireIncrease::FireIncrease(){
	m_Delete = false;

	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> FireIncreaseMat = Swallow::FlatColourMaterial::Create();
	FireIncreaseMat->SetColour(glm::vec4(1.0f, 0.f, 0.f, 1.f));
	SetMaterial(FireIncreaseMat);
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> FireIncreaseMat = Swallow::TextureMaterial::Create();
	FireIncreaseMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(FireIncreaseMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("FireIncrease", "FireIncrease"));
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
}

void	FireIncrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	FireIncrease::CanDelete()
{
	return m_Delete;
}
#pragma endregion
#pragma region FireDecrease
FireDecrease::FireDecrease(){
	m_Delete = false;

	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> FireDecreaseMat = Swallow::FlatColourMaterial::Create();
	FireDecreaseMat->SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.f));
	SetMaterial(FireDecreaseMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> FireDecreaseMat = Swallow::TextureMaterial::Create();
	FireDecreaseMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(FireDecreaseMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("FireDecrease", "FireDecrease"));
	
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void	FireDecrease::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}
bool FireDecrease::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region BombUp
BombUp::BombUp(){
	m_Delete = false;
	
	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombUpMat = Swallow::FlatColourMaterial::Create();
	BombUpMat->SetColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.f));
	SetMaterial(BombUpMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> BombUpMat = Swallow::TextureMaterial::Create();
	BombUpMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(BombUpMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("BombUp", "BombUp"));
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void	BombUp::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	BombUp::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region BombDown
BombDown::BombDown(){
	m_Delete = false;
	
	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombDownMat = Swallow::FlatColourMaterial::Create();
	BombDownMat->SetColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.f));
	SetMaterial(BombDownMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> BombDownMat = Swallow::TextureMaterial::Create();
	BombDownMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(BombDownMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("BombDown", "BombDown"));
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void BombDown::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	BombDown::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region SpeedUp
SpeedUp::SpeedUp(){
	m_Delete = false;

	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SpeedUpMat = Swallow::FlatColourMaterial::Create();
	SpeedUpMat->SetColour(glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
	SetMaterial(SpeedUpMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> SpeedUpMat = Swallow::TextureMaterial::Create();
	SpeedUpMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(SpeedUpMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("SpeedUp", "SpeedUp"));

	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void	SpeedUp::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	SpeedUp::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region SpeedDown
SpeedDown::SpeedDown(){
	m_Delete = false;

	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SpeedDownMat = Swallow::FlatColourMaterial::Create();
	SpeedDownMat->SetColour(glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
	SetMaterial(SpeedDownMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> SpeedDownMat = Swallow::TextureMaterial::Create();
	SpeedDownMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(SpeedDownMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("SpeedDown", "SpeedDown"));
	
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void SpeedDown::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	SpeedDown::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region BombsCanBypassWalls
BombsCanBypassWalls::BombsCanBypassWalls(){
	m_Delete = false;

	/*
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> BombsCanBypassWallsMat = Swallow::FlatColourMaterial::Create();
	BombsCanBypassWallsMat->SetColour(glm::vec4(0.0f, 1.0f, 1.0f, 1.f));
	SetMaterial(BombsCanBypassWallsMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> BombsCanBypassWallsMat = Swallow::TextureMaterial::Create();
	BombsCanBypassWallsMat->SetTexture(Swallow::AssetManager::FetchTexture("PickupsTexture"));
	SetMaterial(BombsCanBypassWallsMat);

	SetVertexArray(Swallow::AssetManager::FetchObject("BombCanBypassWalls", "BombCanBypassWalls"));
	
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void BombsCanBypassWalls::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}

bool	BombsCanBypassWalls::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region SoftBlockPass
SoftBlockPass::SoftBlockPass(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SoftBlockPassMat = Swallow::FlatColourMaterial::Create();
	SoftBlockPassMat->SetColour(glm::vec4(1.f, 1.f, 1.f, 1.f));
	SetMaterial(SoftBlockPassMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(0.5f, 1.5f, 0.5f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void SoftBlockPass::OnUpdate(Swallow::Timestep& time)
{
	this->m_TimeRemaining -= time.GetSeconds();
	if (m_TimeRemaining <= 0)
		m_Delete = true;
}
bool	SoftBlockPass::CanDelete()
{
	return m_Delete;
}

#pragma endregion
#pragma region Key

Key::Key(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SoftBlockPassMat = Swallow::FlatColourMaterial::Create();
	SoftBlockPassMat->SetColour(glm::vec4(1.f, 1.f, 0.3f, 1.f));
	SetMaterial(SoftBlockPassMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(0.5f, 1.5f, 0.5f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void Key::OnUpdate(Swallow::Timestep& time)
{
	static_cast<void>(time);
}
bool	Key::CanDelete()
{
	return m_Delete;
}

#pragma endregion

#pragma region Exit

Exit::Exit(){
	m_Delete = false;
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> SoftBlockPassMat = Swallow::FlatColourMaterial::Create();
	SoftBlockPassMat->SetColour(glm::vec4(1.f, 0.f, 1.f, 1.f));
	SetMaterial(SoftBlockPassMat);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	#ifdef SW_DEBUG
		GetTransform()->SetScale(glm::vec3(0.5f, 1.5f, 0.5f));
	#else
		GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	#endif
};

void Exit::OnUpdate(Swallow::Timestep& time)
{
	static_cast<void>(time);
}
bool	Exit::CanDelete()
{
	return m_Delete;
}

#pragma endregion
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
	case PowerUpTypes::eSpeedUp:
		return std::make_shared<SpeedUp>();
	case PowerUpTypes::eSpeedDown:
		return std::make_shared<SpeedDown>();
	case PowerUpTypes::eBombsCanBypassWalls:
		return std::make_shared<BombsCanBypassWalls>();
	case PowerUpTypes::eSoftBlockPass:
		return std::make_shared<SoftBlockPass>();
	case PowerUpTypes::eKey:
		return std::make_shared<Key>();
	case PowerUpTypes::eExit:
		return std::make_shared<Exit>();
	default:
		return nullptr;
	}
}
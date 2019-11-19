#include "BombermanApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/Renderer/material/CharMaterial.hpp"
#include "Swallow/Renderer/texture/TextureMaterial.hpp"
#include "Swallow/AssetManager/AssetManager.hpp"

BombermanApp::BombermanApp()
{
	Swallow::FlatColourMaterial::Init();
	Swallow::AnimationMaterial::Init();
	Swallow::CharMaterial::Init();
	Swallow::TextureMaterial::Init();
	Swallow::AssetManager::LoadObject("Bomb", "assets/Models/Bomb.obj");
	//Swallow::AssetManager::LoadObject("Bomberman", "assets/Models/Bomberman.obj");
	Swallow::AssetManager::LoadObject("Bomberman", "assets/Models/BombermanAnim.obj");
	Swallow::AssetManager::LoadObject("BombermanIdle", "assets/Models/BombermanAnimIdle.obj");
	Swallow::AssetManager::LoadObject("Cube", "assets/Models/Cube.obj");
	Swallow::AssetManager::LoadObject("IndestructableWall", "assets/Models/Indestructable_Wall.obj");
	Swallow::AssetManager::LoadObject("DestructableWall", "assets/Models/Destructable_Wall.obj");
	Swallow::AssetManager::LoadObject("EmptyQuad", "assets/Models/EmptyQuad.obj");
	Swallow::AssetManager::LoadTexture("Atlas", "assets/Models/atlas.png", false);
	Swallow::AssetManager::LoadTexture("BomberManColor", "assets/Models/BombermanColor.png", false);

	//Enemies
	//Textures
	Swallow::AssetManager::LoadTexture("EnemyTexture", "assets/Models/Characters/Enemies/Textures/textureAtlas_Enemy.png", false);
	//Models
	Swallow::AssetManager::LoadObject("Enemy", "assets/Models/Characters/Enemies/Enemy.obj");
	


	//Pickups
	//Texture
	Swallow::AssetManager::LoadTexture("PickupsTexture", "assets/Models/Pickups/Pallete1.png", false);
	
	//Models
	Swallow::AssetManager::LoadObject("BombCanBypassWalls", "assets/Models/Pickups/BombCanBypassWalls.obj");
	Swallow::AssetManager::LoadObject("BombUp", "assets/Models/Pickups/BombUp.obj");
	Swallow::AssetManager::LoadObject("BombDown", "assets/Models/Pickups/BombDown.obj");
	Swallow::AssetManager::LoadObject("FireIncrease", "assets/Models/Pickups/FireIncrease.obj");
	Swallow::AssetManager::LoadObject("FireDecrease", "assets/Models/Pickups/FireDecrease.obj");
	Swallow::AssetManager::LoadObject("SpeedDown", "assets/Models/Pickups/SpeedDown.obj");
	Swallow::AssetManager::LoadObject("SpeedUp", "assets/Models/Pickups/SpeedUp.obj");

	Swallow::AssetManager::ListMeshes("FireIncrease");
	Swallow::AssetManager::ListMeshes("FireDecrease");

	m_GameLayer = std::make_shared<GameLayer>();
	m_GUILayer = std::make_shared<GUILayer>();
	m_MenuLayer = std::make_shared<MenuLayer>();
	m_BackgroundLayer = std::make_shared<Background>();
	LoadMenu();
}

BombermanApp::~BombermanApp()
{

}

void BombermanApp::LoadMenu()
{
	PushLayer(m_MenuLayer);
}

void BombermanApp::UnloadMenu()
{
	PopLayer(m_MenuLayer);
}

void BombermanApp::UnloadGame()
{
	PopLayer(m_GameLayer);
	PopOverlay(m_GUILayer);
	PopLayer(m_BackgroundLayer);
}

void BombermanApp::LoadGame()
{
	m_GameLayer->SetSpawnChance(m_MenuLayer->GetChance());
	m_GameLayer->SetSave(m_MenuLayer->GetSave());
	PushLayer(m_BackgroundLayer);
	PushLayer(m_GameLayer);
	PushOverlay(m_GUILayer);
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new BombermanApp());
}
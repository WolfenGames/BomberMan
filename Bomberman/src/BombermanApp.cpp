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
	// Swallow::AssetManager::LoadObject("Bomberman", "assets/Models/BombermanAnim.obj");
	Swallow::AssetManager::LoadObject("Cube", "assets/Models/Cube.obj");
	// Swallow::AssetManager::LoadObject("IndestructableWall", "assets/Models/Indestructable_Wall.obj");
	// Swallow::AssetManager::LoadObject("DestructableWall", "assets/Models/Destructable_Wall.obj");
	Swallow::AssetManager::LoadObject("EmptyQuad", "assets/Models/EmptyQuad.obj");
	// Swallow::AssetManager::LoadTexture("Atlas", "assets/Models/atlas.png", false);

	Swallow::AssetManager::ListMeshes("DestructableWall");

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
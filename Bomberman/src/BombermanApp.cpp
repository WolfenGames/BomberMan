#include "BombermanApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"
#include "Swallow/Renderer/material/CharMaterial.hpp"

BombermanApp::BombermanApp()
{
	Swallow::FlatColourMaterial::Init();
	Swallow::CharMaterial::Init();
	Swallow::MenuMaterial::Init();
	Swallow::AssetManager::LoadObject("Bomb", "assets/Models/Bomb.obj");
	Swallow::AssetManager::LoadObject("Bomberman", "assets/Models/Bomberman.obj");
	m_GameLayer = std::make_shared<GameLayer>();
	m_GUILayer = std::make_shared<GUILayer>();
	m_MenuLayer = std::make_shared<MenuLayer>();
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
}

void BombermanApp::LoadGame()
{
	m_GameLayer->SetMapSize(m_MenuLayer->GetMapSize());
	m_GameLayer->SetSpawnChance(m_MenuLayer->GetChance());
	PushLayer(m_GameLayer);
	PushOverlay(m_GUILayer);
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new BombermanApp());
}
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
	Swallow::AssetManager::LoadObject("Cube", "assets/Models/Cube.obj");
	Swallow::AssetManager::LoadObject("EmptyQuad", "assets/Models/EmptyQuad.obj");

	m_GameLayer = std::make_shared<GameLayer>();
	m_GUILayer = std::make_shared<GUILayer>();
	m_MenuLayer = std::make_shared<MainMenu>();
	m_BackgroundLayer = std::make_shared<Background>();
	m_OptionsLayer = std::make_shared<OptionsMenu>();
	m_ExitLayer = std::make_shared<ExitMenu>();
	LoadMenu();
}

BombermanApp::~BombermanApp()
{

}

void BombermanApp::LoadMenu()
{
	PushLayer(m_MenuLayer);
}

void BombermanApp::LoadOptions()
{
	PushLayer(m_OptionsLayer);
}

void BombermanApp::UnloadOptions()
{
	PopLayer(m_OptionsLayer);
}

void BombermanApp::LoadExit()
{
	PushLayer(m_ExitLayer);
}

void BombermanApp::UnloadExit()
{
	PopLayer(m_ExitLayer);
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
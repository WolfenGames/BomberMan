#include "BombermanApp.hpp"
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

BombermanApp::BombermanApp()
{
	Swallow::FlatColourMaterial::Init();
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
	PushLayer(m_GameLayer);
	PushOverlay(m_GUILayer);
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new BombermanApp());
}
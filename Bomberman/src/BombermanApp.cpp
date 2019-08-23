#include "BombermanApp.hpp"
#include "GameLayer.hpp"
#include "GUILayer.hpp"

BombermanApp::BombermanApp()
{
	PushLayer(new GameLayer());
	PushLayer(new GUILayer());
}

BombermanApp::~BombermanApp()
{

}

Swallow::Application* Swallow::CreateApplication()
{
	return (new BombermanApp());
}
#include "BombermanApp.hpp"
#include "GameLayer.hpp"

BombermanApp::BombermanApp()
{
	PushLayer(new GameLayer());
}

BombermanApp::~BombermanApp()
{

}

Swallow::Application* Swallow::CreateApplication()
{
	return (new BombermanApp());
}
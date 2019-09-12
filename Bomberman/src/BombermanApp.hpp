#pragma once
#include <Swallow.hpp>
#include "GameLayer.hpp"
#include "GUILayer.hpp"
#include "MenuLayer.hpp"

class BombermanApp : public Swallow::Application
{
public:
	BombermanApp();
	virtual ~BombermanApp();

	void LoadMenu();
	void UnloadMenu();
	void UnloadGame();
	void LoadGame();
	void LoadModels(const std::vector<std::string> &assetPaths)
	void LoadModelAsset(const std::string &path)

private:
	BombermanApp(const BombermanApp &s) = default;
	BombermanApp &operator=(const BombermanApp &s) = default;

	Swallow::Ref<GameLayer> m_GameLayer;
	Swallow::Ref<GUILayer> m_GUILayer;
	Swallow::Ref<MenuLayer> m_MenuLayer;
};
#pragma once
#include <Swallow.hpp>
#include "GameLayer.hpp"
#include "GUILayer.hpp"
#include "MenuLayer.hpp"
#include "menus/MainMenu.hpp"

class BombermanApp : public Swallow::Application
{
public:
	BombermanApp();
	virtual ~BombermanApp();

	void LoadMenu();
	void UnloadMenu();
	void UnloadGame();
	void LoadGame();

	void LoadOptions();
	void UnloadOptions();

private:
	BombermanApp(const BombermanApp &s) = delete;
	BombermanApp &operator=(const BombermanApp &s) = delete;

	Swallow::Ref<GameLayer> m_GameLayer;
	Swallow::Ref<GUILayer> m_GUILayer;
	Swallow::Ref<MenuLayer> m_MenuLayer;
	Swallow::Ref<OptionsMenu> m_OptionsLayer;
};
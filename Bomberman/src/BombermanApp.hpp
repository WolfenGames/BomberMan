#pragma once
#include <Swallow.hpp>
#include "GameLayer.hpp"
#include "GUILayer.hpp"
#include "MenuLayer.hpp"
#include "menus/MainMenu.hpp"
#include "Background.hpp"

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
	inline Swallow::Ref<GameLayer> GetGameLayer() { return m_GameLayer; }

private:
	BombermanApp(const BombermanApp &s) = delete;
	BombermanApp &operator=(const BombermanApp &s) = delete;

	Swallow::Ref<GameLayer> m_GameLayer;
	Swallow::Ref<GUILayer> m_GUILayer;
	Swallow::Ref<MenuLayer> m_MenuLayer;
	Swallow::Ref<OptionsMenu> m_OptionsLayer;
	// Swallow::Ref<KeyBindingsMenu> m_KeyBindingsLayer;
	Swallow::Ref<Background> m_BackgroundLayer;
};
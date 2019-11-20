#pragma once
#include <Swallow.hpp>
#include "GameLayer.hpp"
#include "GUILayer.hpp"
#include "MenuLayer.hpp"
#include "menus/MainMenu.hpp"
#include "Background.hpp"
#include "settings/Settings.hpp"

class BombermanApp : public Swallow::Application
{
	public:
		BombermanApp(Swallow::WindowProps *props = nullptr);
		virtual ~BombermanApp();

		void LoadMenu();
		void UnloadMenu();
		void UnloadGame();
		void LoadGame();

		void LoadOptions();
		void UnloadOptions();
		void LoadExit();
		void UnloadExit();
		void LoadLoad();
		void UnloadLoad();
		void LoadKeys();
		void UnloadKeys();
		void LoadNewGame();
		void UnloadNewGame();
		void LoadPause();
		void UnloadPause();

		inline Swallow::Ref<GameLayer> GetGameLayer() { return m_GameLayer; }
		inline Swallow::Ref<Settings> GetSettings() { return m_Settings; };
private:
	// BombermanApp(const BombermanApp &s) = default;
	// BombermanApp &operator=(const BombermanApp &s) = default;

	private:
		BombermanApp(const BombermanApp &s) = delete;
		BombermanApp &operator=(const BombermanApp &s) = delete;

		Swallow::Ref<GameLayer> m_GameLayer;
		Swallow::Ref<GUILayer> m_GUILayer;
		Swallow::Ref<MenuLayer> m_MenuLayer;
		// Swallow::Ref<KeyBindingsMenu> m_KeyBindingsLayer;
		Swallow::Ref<Background> m_BackgroundLayer;
		Swallow::Ref<OptionsMenu> m_OptionsLayer;
		Swallow::Ref<ExitMenu> m_ExitLayer;
		Swallow::Ref<LoadingMenu> m_LoadLayer;
		Swallow::Ref<KeyMenu> m_KeyLayer;
		Swallow::Ref<Settings> m_Settings;
		Swallow::Ref<NewGame> m_NewGameLayer;
		Swallow::Ref<PauseMenu> m_PauseLayer;
};
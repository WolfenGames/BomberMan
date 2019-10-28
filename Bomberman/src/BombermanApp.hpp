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
		void LoadExit();
		void UnloadExit();
		void LoadLoad();
		void UnloadLoad();

		inline Swallow::Ref<GameLayer> GetGameLayer() { return m_GameLayer; }

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
};
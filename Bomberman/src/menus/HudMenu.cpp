/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HudMenu.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:18:50 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/20 15:59:10 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HudMenu.hpp"
#include "../BombermanApp.hpp"

#define SCORE 0
#define LIVES 1
#define KEY 2
#define GHOST 3
#define SUPER 4
#define POWERUPS 5
#define BOMBS 6
#define BOMBSTR 7

HudMenu::HudMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

    Swallow::Ref<Swallow::TextureMaterialInstance>  m_Material = Swallow::MenuBackgroundMaterial::Create();
    m_Material->SetTexture(Swallow::AssetManager::FetchTexture("HUDBackground"));

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->SetMaterial(m_Material);
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, -7.5f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 2.5f, 0.0f));
	m_Menu->GetText()->GetTransform()->SetScale(glm::vec3(0.0f, 0.0f, 0.0f));
	m_Menu->AddButton("Score - 0", -9.0f, -7.0f, m_Camera);
	m_Menu->AddButton("Lives - 0", -9.0f, -9.0f, m_Camera);
	m_Menu->AddButton("", 2.0f, -9.0f, m_Camera);
	m_Menu->AddButton("", 4.0f, -9.0f, m_Camera);
	m_Menu->AddButton("", 7.0f, -9.0f, m_Camera);
	m_Menu->AddButton("Power ups", 4.0f, -7.0f, m_Camera);
	m_Menu->AddButton("Bombs - 1", -6.0f, -7.0f, m_Camera);
	m_Menu->AddButton("Bomb Strength - 1", -6.0f, -9.0f, m_Camera);
	for (auto a : m_Menu->GetButtons())
		a->GetText()->GetTransform()->SetScale(glm::vec3(0.4f, 0.8f, 0.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void HudMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(HudMenu::OnKeyPressed));
}

bool HudMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		GameLayer::IsPaused = true;
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadPause();
	}
	else
		return false;
	return true;
}

void HudMenu::OnUpdate(Swallow::Timestep ts)
{
	static_cast<void>(ts);
	Swallow::Renderer::BeginScene(m_Camera);

	UpdateButtons();
	Swallow::Renderer::Submit(m_Menu->GetBackground());
	Swallow::Renderer::Submit(m_Menu->GetText());
	for (auto a : m_Menu->GetButtons())
	{
		Swallow::Renderer::Submit(a->GetBackground());
		Swallow::Renderer::Submit(a->GetText());
	}
	Swallow::Renderer::EndScene();
}

void HudMenu::UpdateButtons()
{
	auto gamelayer = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
	if (!gamelayer->GetLevel())
		return ;
	auto player = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->GetLevel()->GetPlayer();
	m_Menu->GetButtons()[SCORE]->GetText()->SetText(("Score - " + std::to_string(gamelayer->GetScore())).c_str());
	m_Menu->GetButtons()[LIVES]->GetText()->SetText(("Lives - " + std::to_string(gamelayer->GetLives())).c_str());
	if (player->Ghost())
		m_Menu->GetButtons()[GHOST]->GetText()->SetText("Ghost");
	else
		m_Menu->GetButtons()[GHOST]->GetText()->SetText("");
	if (player->GetBombsCanBypassWalls())
		m_Menu->GetButtons()[SUPER]->GetText()->SetText("Super Bombs");
	else
		m_Menu->GetButtons()[SUPER]->GetText()->SetText("");
	if (player->HasKey())
		m_Menu->GetButtons()[KEY]->GetText()->SetText("Key");
	else
		m_Menu->GetButtons()[KEY]->GetText()->SetText("");
	m_Menu->GetButtons()[BOMBS]->GetText()->SetText(("Bombs - " + std::to_string(player->GetBombCount() + 1)).c_str());
	m_Menu->GetButtons()[BOMBSTR]->GetText()->SetText(("Bomb Strength - " + std::to_string(player->GetFireDistance() - 1)).c_str());
	m_Menu->RecalculateButtons();
}
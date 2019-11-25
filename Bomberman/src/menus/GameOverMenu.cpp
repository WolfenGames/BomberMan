#include "GameOverMenu.hpp"
#include "../BombermanApp.hpp"

GameOverMenu::GameOverMenu() : m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
    m_Camera.SetPosition(glm::vec3(0, 0, 0));
    m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void GameOverMenu::OnAttach()
{
    MenuLayer::OnAttach();
    Swallow::Ref<GameLayer> g = static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer();
    m_Menu->GetButtons().clear();
	m_Menu->AddButton("Game Over", 0.0f, 2.0f, m_Camera);
    m_Menu->AddButton("Score", 0.0f, -1.0f, m_Camera);
    m_Menu->AddButton(std::to_string(g->GetScore()).c_str(), 0.0f, -2.5f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
    m_Timer = 3;
    m_hasBeenReset = false;
}

void GameOverMenu::OnUpdate(Swallow::Timestep ts)
{
    MenuLayer::OnUpdate(ts);
    m_Timer -= ts.GetSeconds();
    if (m_Timer <= 0)
    {
        //if (!m_hasBeenReset)
        //{
            SW_INFO("JKASAS");
            static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadGameOver();
            static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
            //m_hasBeenReset = true;
        //}
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:26:52 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/28 15:04:58 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainMenu.hpp"
#include "../BombermanApp.hpp"

#define QUIT 0
#define OPTIONS 1
#define LOAD 2
#define NEW 3

MainMenu::MainMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Quit game", 0.0f, -2.0f, m_Camera);
	m_Menu->AddButton("Options", 0.0f, 1.0f, m_Camera);
	m_Menu->AddButton("Load game", 0.0f, 4.0f, m_Camera);
	m_Menu->AddButton("New game", 0.0f, 7.0f, m_Camera);
	m_Menu->GetButtons().back()->GetBackground()->GetTransform()->SetScale(glm::vec3(2.1f, 1.0f, 0.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void MainMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(MainMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(MainMenu::OnKeyPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(MainMenu::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::WindowResizeEvent>(BIND_EVENT_FN(MenuLayer::OnWindowResize));
}


bool MainMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (m_Menu->GetButtons()[QUIT]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadExit();
        return true;
	}
	if (m_Menu->GetButtons()[NEW]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
		return true;
	}
	if (m_Menu->GetButtons()[OPTIONS]->MouseInBounds(x, y))
    {
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadOptions();
        return true;
    }
	if (m_Menu->GetButtons()[LOAD]->MouseInBounds(x, y))
    {
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadLoad();
        return true;
    }
	return false;
}

bool MainMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadExit();
	}
	else if (e.GetKeyCode() == SW_KEY_SPACE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
	}
	else
		return false;
	return true;
}

bool MainMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;

	for (size_t i = 0; i < m_Menu->GetButtons().size(); i++)
	{
		if (m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return false;
}
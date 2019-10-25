/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:26:52 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/25 16:39:49 by ppreez           ###   ########.fr       */
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
	// m_Menu->GetButtons().insert
	m_Menu->GetButtons().back()->GetBackground()->GetTransform()->SetScale(glm::vec3(2.1f, 1.0f, 0.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void MainMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(MainMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(MainMenu::OnKeyPressed));
}


bool MainMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	glm::vec2 bl = m_Menu->GetButtons()[QUIT]->GetBottomLeft();
	glm::vec2 tr = m_Menu->GetButtons()[QUIT]->GetTopRight();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadExit();
        return true;
	}
	bl = m_Menu->GetButtons()[NEW]->GetBottomLeft();
	tr = m_Menu->GetButtons()[NEW]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
		return true;
	}
    bl = m_Menu->GetButtons()[OPTIONS]->GetBottomLeft();
	tr = m_Menu->GetButtons()[OPTIONS]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
    {
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadOptions();
        return true;
    }
    bl = m_Menu->GetButtons()[LOAD]->GetBottomLeft();
	tr = m_Menu->GetButtons()[LOAD]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
    {
        SW_CORE_INFO("LOAD MENU LOADED");
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

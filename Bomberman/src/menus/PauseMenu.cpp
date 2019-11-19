/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PauseMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:10:39 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/15 16:06:03 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PauseMenu.hpp"
#include "../BombermanApp.hpp"

#define RESUME 0
#define OPTIONS 1
#define QUIT 2

PauseMenu::PauseMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Resume", 0.0f, 2.0f, m_Camera);
	m_Menu->AddButton("Options", 0.0f, 0.0f, m_Camera);
	m_Menu->AddButton("Quit", 0.0f, -2.0f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void PauseMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(PauseMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(PauseMenu::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(PauseMenu::OnKeyPressed));
}

bool PauseMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	
	if (m_Menu->GetButtons()[QUIT]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadPause();
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadGame();		
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
	}
    if (m_Menu->GetButtons()[RESUME]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadPause();
		GameLayer::IsPaused = false;
	}
    if (m_Menu->GetButtons()[OPTIONS]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadOptions();
	}
	return true;
}

bool PauseMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
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

bool PauseMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadPause();
	}
	return true;
}

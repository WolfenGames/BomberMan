/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExitMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:31:27 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/07 15:49:39 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExitMenu.hpp"
#include "../BombermanApp.hpp"

#define YES 1
#define NO 2

ExitMenu::ExitMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Exit game?", 0.0f, 2.0f, m_Camera);
    m_Menu->AddButton("Yes", 0.0f, -1.0f, m_Camera);
    m_Menu->AddButton("No", 2.0f, -1.0f, m_Camera);
	m_Menu->GetButtons()[NO]->GetBackground()->GetTransform()->SetScale(glm::vec3(0.7f, 1.0f, 1.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void ExitMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(ExitMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(ExitMenu::OnKeyPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(ExitMenu::OnMouseMovedEvent));
}


bool ExitMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (m_Menu->GetButtons()[YES]->MouseInBounds(x, y))
		Swallow::Application::Get().End();
	if (m_Menu->GetButtons()[NO]->MouseInBounds(x, y))
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadExit();
	return true;
}

bool ExitMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_SPACE)
	{
		Swallow::Application::Get().End();
	}
	else if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadExit();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
	}
	else
		return false;
	return true;
}

bool ExitMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;

	for (size_t i = 1; i < m_Menu->GetButtons().size(); i++)
	{
		if (m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return true;
}
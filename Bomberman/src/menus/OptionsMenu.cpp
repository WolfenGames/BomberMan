/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionsMenu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:33:23 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/27 15:19:46 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OptionsMenu.hpp"
#include "../BombermanApp.hpp"

#define BACK 0
#define SOUND 1
#define RESOLUTION 2
#define KEYS 3
#define SWITCH 4

OptionsMenu::OptionsMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Back", 0.0f, -2.0f, m_Camera);
	m_Menu->AddButton("Sound", 0.0f, 1.0f, m_Camera);
	m_Menu->AddButton("Resolution", 0.0f, 4.0f, m_Camera);
	m_Menu->AddButton("Key Bindings", 0.0f, 7.0f, m_Camera);
	m_Menu->AddButton("Off", 3.0f, 1.0f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void OptionsMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(OptionsMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(OptionsMenu::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(OptionsMenu::OnKeyPressed));
}

bool OptionsMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (m_Menu->GetButtons()[SWITCH]->MouseInBounds(x, y))
    {
        m_Menu->GetButtons()[SWITCH]->GetText()->SetText("On");
		return true;
    }
	if (m_Menu->GetButtons()[RESOLUTION]->MouseInBounds(x, y))
	{
		SW_CORE_INFO("Resolution");
		return true;
	}
	if (m_Menu->GetButtons()[BACK]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadOptions();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
		return true;
	}
	if (m_Menu->GetButtons()[KEYS]->MouseInBounds(x, y))
	{
		SW_CORE_INFO("Key Bindings");
		return true;
	}
	return false;
}


bool OptionsMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;

	for (size_t i = 0; i < m_Menu->GetButtons().size(); i++)
	{

		if (i != SOUND && m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return false;
}

bool OptionsMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadOptions();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
	}
	else
		return false;
	return true;
}

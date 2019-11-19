/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyMenu.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:55:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/11 15:25:27 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyMenu.hpp"
#include "../BombermanApp.hpp"
 
#define BACK 0

KeyMenu::KeyMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f), m_KeyCount(0), m_Changed(0), m_InputActive(false), m_ActiveButton(-1)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
    float f = 8.0f;
	for (auto a : static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeybindings())
    {
        m_Menu->AddButton(a.first.c_str(), -2.0f, f, m_Camera);
		std::string key = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeyMap()[a.second];
        f -= 2.0f;
		m_KeyCount++;
    }
	f = 8.0f;
	for (auto a : static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeybindings())
	{
		std::string key = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeyMap()[a.second];
        m_Menu->AddButton(key.c_str(), 2.0f, f, m_Camera);
        f -= 2.0f;
		m_KeyCount++;
	}
	m_KeyCount /= 2;
	m_Menu->AddButton("Back", 0.0f, f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void KeyMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(KeyMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(KeyMenu::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(KeyMenu::OnKeyPressed));
}

bool KeyMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (m_Menu->GetButtons().back()->MouseInBounds(x, y))
	{
		if (m_InputActive == true)
		{
			m_Menu->GetButtons()[m_ActiveButton]->GetText()->SetText(m_TempText);
			m_Menu->GetButtons()[m_ActiveButton]->Recalculate();
			m_InputActive = false;
			m_ActiveButton = -1;
		}
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->SaveSettings();
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadKeys();
		return true;
	}
	size_t i = 0;
	for (auto a : m_Menu->GetButtons())
	{
		if (m_InputActive == true && a->MouseInBounds(x, y))
		{
			m_Menu->GetButtons()[m_ActiveButton]->GetText()->SetText(m_TempText);
			m_Menu->GetButtons()[m_ActiveButton]->Recalculate();
			m_ActiveButton = i;
			m_InputAction = m_Menu->GetButtons()[i - m_KeyCount]->GetText()->GetString();
			m_TempText = m_Menu->GetButtons()[i]->GetText()->GetString();
			m_Menu->GetButtons()[i]->GetText()->SetText("");
			m_Menu->GetButtons()[i]->Recalculate();
		}
		else if (m_InputActive == false && i >= m_KeyCount && i < m_Menu->GetButtons().size() - 1 && a->MouseInBounds(x, y))
		{
			m_InputActive = true;
			m_ActiveButton = i;
			m_InputAction = m_Menu->GetButtons()[i - m_KeyCount]->GetText()->GetString();
			m_TempText = m_Menu->GetButtons()[i]->GetText()->GetString();
			m_Menu->GetButtons()[i]->GetText()->SetText("");
			m_Menu->GetButtons()[i]->Recalculate();
			m_Changed = 1;
		}
		i++;
	}
	return true;
}

bool KeyMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
{
	static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;

	for (size_t i = 0; i < m_Menu->GetButtons().size(); i++)
	{

		if (i >= m_KeyCount && m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return true;
}

bool KeyMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	std::string input;
	std::string conflict;
	if (m_InputActive)
	{
		input += static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeyMap()[e.GetKeyCode()];
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->SetKeybinding(m_InputAction, e.GetKeyCode());
		m_Menu->GetButtons()[m_ActiveButton]->GetText()->SetText(input);
		m_InputActive = false;
		m_Menu->RecalculateButtons();
		m_ActiveButton = -1;
		return true;
	}
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->SaveSettings();
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadKeys();
	}
	else
		return false;
	return true;
}
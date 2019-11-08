/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyMenu.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:55:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/08 15:49:55 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyMenu.hpp"
#include "../BombermanApp.hpp"

#define BACK 0

KeyMenu::KeyMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
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
        m_Menu->AddButton(key.c_str(), 2.0f, f, m_Camera);
        f -= 2.0f;
    }
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
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadKeys();
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

		if (m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return true;
}

bool KeyMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadKeys();
	else
		return false;
	return true;
}

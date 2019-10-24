/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionsMenu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:33:23 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/24 16:03:55 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OptionsMenu.hpp"
#include "../BombermanApp.hpp"

#define BACK 0
#define SOUND 1
#define RESOLUTION 2
#define KEYS 3

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
	m_Menu->AddButton("X", 3.0f, 1.0f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void OptionsMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(OptionsMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(OptionsMenu::OnKeyPressed));
}


bool OptionsMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	glm::vec2 bl = m_Menu->GetButtons()[SOUND]->GetBottomLeft();
	glm::vec2 tr = m_Menu->GetButtons()[SOUND]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
    {
        SW_CORE_INFO("Sound");
    }
	bl = m_Menu->GetButtons()[RESOLUTION]->GetBottomLeft();
	tr = m_Menu->GetButtons()[RESOLUTION]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		SW_CORE_INFO("Resolution");
		return true;
	}
    bl = m_Menu->GetButtons()[BACK]->GetBottomLeft();
	tr = m_Menu->GetButtons()[BACK]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadOptions();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
		return true;
	}
    bl = m_Menu->GetButtons()[KEYS]->GetBottomLeft();
	tr = m_Menu->GetButtons()[KEYS]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		SW_CORE_INFO("KEY BINDINGS");
		return true;
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

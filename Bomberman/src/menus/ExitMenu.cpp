/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExitMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:31:27 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/25 17:02:26 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../BombermanApp.hpp"

ExitMenu::ExitMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Exit game?", 0.0f, 2.0f);
    m_Menu->AddButton("Yes", -1.0f, -1.0f);
    // m_Menu->AddButton("No", 1.0f, -1.0f);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void ExitMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(ExitMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(ExitMenu::OnKeyPressed));
}


bool ExitMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	glm::vec2 bl = m_Menu->GetButtons()[1]->GetBottomLeft();
	glm::vec2 tr = m_Menu->GetButtons()[1]->GetTopRight();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
    SW_CORE_INFO("X: {}", x);
    SW_CORE_INFO("Y: {}\n", y);
    SW_CORE_INFO("bl.x: {}\n", bl.x);
    SW_CORE_INFO("bl.y: {}\n", bl.y);
    SW_CORE_INFO("tr.x: {}\n", tr.x);
    SW_CORE_INFO("tr.y: {}\n", tr.y);
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
		Swallow::Application::Get().End();
	bl = m_Menu->GetButtons()[2]->GetBottomLeft();
	tr = m_Menu->GetButtons()[2]->GetTopRight();
	if (x > bl.x && x < tr.x && y < bl.y && y > tr.y)
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadExit();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadMenu();
		return true;
	}
	return false;
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

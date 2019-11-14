/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewGame.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:57:43 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/08 16:06:24 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NewGame.hpp"
#include "../BombermanApp.hpp"

#define INPUT 0
#define START 1
#define BACK 2

NewGame::NewGame()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->AddButton("Enter name", 0.0f, 3.0f, m_Camera);
	m_Menu->AddButton("Start", 0.0f, 0.0f, m_Camera);
	m_Menu->AddButton("Back", 0.0f, -2.0f, m_Camera);
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void NewGame::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(NewGame::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(NewGame::OnMouseMovedEvent));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(NewGame::OnKeyPressed));
}

bool NewGame::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	
	if (m_Menu->GetButtons()[BACK]->MouseInBounds(x, y))
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadNewGame();
    if (m_Menu->GetButtons()[START]->MouseInBounds(x, y))
	{
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadNewGame();
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
	}
	if (m_Menu->GetButtons()[INPUT]->MouseInBounds(x, y))
	{
		m_InputActive = true;
		m_Input = "";
		m_Menu->GetButtons()[INPUT]->GetText()->SetText(m_Input);
		m_Menu->GetButtons()[INPUT]->Recalculate();
	}
	return true;
}

bool NewGame::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
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

bool NewGame::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (m_InputActive && e.GetKeyCode() == SW_KEY_ENTER)
	{
		m_InputActive = false;
		m_Menu->GetButtons()[INPUT]->UnhighlightBackground();
		return true;
	}
	if (m_InputActive)
	{
		int key = e.GetKeyCode();
		if ((key > 47 && key < 58) || (key > 64 && key < 91))
		{
			m_Input += static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetKeyMap()[e.GetKeyCode()];
			m_Menu->GetButtons()[INPUT]->GetText()->SetText(m_Input);
			m_Menu->GetButtons()[INPUT]->Recalculate();
		}
		if (key == SW_KEY_BACKSPACE)
		{
			m_Input.pop_back();
			m_Menu->GetButtons()[INPUT]->GetText()->SetText(m_Input);
			m_Menu->GetButtons()[INPUT]->Recalculate();
		}
		return true;
	}
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
        static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadNewGame();
	else
		return false;
	return true;
}

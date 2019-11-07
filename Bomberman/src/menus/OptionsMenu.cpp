/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionsMenu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:33:23 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/07 18:12:56 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OptionsMenu.hpp"
#include "../BombermanApp.hpp"

#define BACK 0
#define SOUND 1
#define RESOLUTION 2
#define KEYS 3
#define SOUND_CYCLE 4
#define RES_CYCLE 5
#define SAVE 6

OptionsMenu::OptionsMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f), m_Changed(0)
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

	std::string btn_name;
	float volume = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetVolume();
	if (volume == 0.0f)
		btn_name = "Off";
	else if (volume <= 0.5f)
		btn_name = "Quiet";
	else
		btn_name = "Loud";
	m_Menu->AddButton(btn_name.c_str(), 5.0f, 1.0f, m_Camera);
	btn_name = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetResolutionString();
	m_Menu->AddButton(btn_name.c_str(), 5.0f, 4.0f, m_Camera);
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
	if (m_Menu->GetButtons()[SOUND_CYCLE]->MouseInBounds(x, y))
    {
		m_Changed = 1;
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->CycleVolume();
		std::string volume_text = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetVolumeString();
		m_Menu->GetButtons()[SOUND_CYCLE]->GetText()->SetText(volume_text);
		m_Menu->GetButtons()[SOUND_CYCLE]->Recalculate();
    }
	if (m_Menu->GetButtons()[RES_CYCLE]->MouseInBounds(x, y))
	{
		m_Changed = 1;
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->CycleResolution();
		std::string res_text = static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->GetResolutionString();
		m_Menu->GetButtons()[RES_CYCLE]->GetText()->SetText(res_text);
		m_Menu->GetButtons()[RES_CYCLE]->Recalculate();
	}
	if (m_Menu->GetButtons()[BACK]->MouseInBounds(x, y))
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadOptions();
	if (m_Menu->GetButtons()[KEYS]->MouseInBounds(x, y))
		static_cast<BombermanApp &>(Swallow::Application::Get()).LoadKeys();
	if (m_Changed == 1)
	{
		m_Changed++;
		m_Menu->AddButton("Save", 3.0f, -2.0f, m_Camera);
		m_Menu->GetButtons()[BACK]->GetText()->SetText("Cancel");
		m_Menu->GetButtons()[BACK]->Recalculate();
		m_Menu->Recalculate();
		m_Menu->RecalculateButtons();
	}
	if (m_Changed == 2 && m_Menu->GetButtons().back()->MouseInBounds(x, y))
	{
		SW_CORE_INFO("CLICKED");
		static_cast<BombermanApp &>(Swallow::Application::Get()).GetSettings()->SaveSettings();
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadOptions();
		m_Menu->GetButtons()[BACK]->GetText()->SetText("Back");
		m_Menu->GetButtons().pop_back();
		m_Menu->Recalculate();
		m_Menu->RecalculateButtons();
		m_Changed = 0;
	}
	return true;
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

		if (i != SOUND && i != RESOLUTION && m_Menu->GetButtons()[i]->MouseInBounds(x, y))
			m_Menu->GetButtons()[i]->HighlightBackground();
		else
			m_Menu->GetButtons()[i]->UnhighlightBackground();
	}
	return true;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadMenu.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:45:41 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/18 11:18:45 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoadMenu.hpp"
#include "../BombermanApp.hpp"
#include <dirent.h>
 
#define BACK 0
#define INPUT 1

LoadingMenu::LoadingMenu()
:m_Camera(-10, 10, -10, 10, 10, -10), map_size(1.0f)
{
	m_Camera.SetPosition(glm::vec3(0, 0, 0));
	m_Camera.SetRotation(glm::vec3(0, 0, 0));
	m_Camera.Recalculate();

	m_Menu = Menu::Create();
	m_Menu->GetBackground()->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Menu->GetBackground()->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
	m_Menu->Recalculate();
	m_Menu->RecalculateButtons();
}

void LoadingMenu::OnEvent(Swallow::Event &e) {
	Swallow::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Swallow::MouseButtonPressedEvent>(BIND_EVENT_FN(LoadingMenu::OnMouseButtonPressed));
	dispatcher.Dispatch<Swallow::KeyPressedEvent>(BIND_EVENT_FN(LoadingMenu::OnKeyPressed));
	dispatcher.Dispatch<Swallow::MouseMovedEvent>(BIND_EVENT_FN(LoadingMenu::OnMouseMovedEvent));
}

bool LoadingMenu::OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e)
{
    static_cast<void>(e);
	float x = Swallow::Input::GetMouseX();
	float y = Swallow::Input::GetMouseY();
	x = ((x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	y = ((y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	if (m_Menu->GetButtons().back()->MouseInBounds(x, y))
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadLoad();
	for (size_t i = 0 ; i < m_Menu->GetButtons().size() - 1 ; i++)
	{
		if (m_Menu->GetButtons()[i]->MouseInBounds(x, y))
		{
			std::string name = m_Menu->GetButtons()[i]->GetText()->GetString();
			GameLayer::IsPaused = false;
			static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadLoad();
			std::ifstream s(std::string("Saves/") + name + ".sav");
			static_cast<BombermanApp &>(Swallow::Application::Get()).GetGameLayer()->SetSave(name);
			static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadMenu();
			static_cast<BombermanApp &>(Swallow::Application::Get()).LoadGame();
		}
	}
	return true;
}

bool LoadingMenu::OnKeyPressed(Swallow::KeyPressedEvent &e)
{
	if (e.GetKeyCode() == SW_KEY_ESCAPE)
		static_cast<BombermanApp &>(Swallow::Application::Get()).UnloadLoad();
	else
		return false;
	return true;
}

bool LoadingMenu::OnMouseMovedEvent(Swallow::MouseMovedEvent &e)
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

void LoadingMenu::OnAttach()
{
	m_Menu->GetButtons().clear();
	float f = AddSaves();
	m_Menu->AddButton("Back", 0.0f, f, m_Camera);
}

void LoadingMenu::OnDetach()
{

}

float LoadingMenu::AddSaves()
{
	DIR *dir;
	struct dirent *dirent;
	std::string name;
	size_t len;
	float f = 6.0f;
	if ((dir = opendir("./Saves/")) == NULL)
	{
		SW_CORE_WARN("Could not open Saves directory.");
		return 0.0f;
	}
	while ((dirent = readdir(dir)) != NULL)
	{
		name = dirent->d_name;
		len = name.find(".sav");
		if (len != name.npos && len > 0)
		{
			SW_CORE_INFO("save: {}", name);
			name = name.substr(0, len);
			m_Menu->AddButton(name.c_str(), 0.0f, f, m_Camera);
			f -= 2.0f;
		}
	}
	closedir(dir);
	return f;
}
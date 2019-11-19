/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/18 13:35:16 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menu.hpp"
#include "Button.hpp"
 
Menu::Menu()
{
    m_Material = Swallow::MenuMaterial::Create();
    m_Material->SetColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    m_Background = Swallow::Primatives::Quad();
    m_Background->SetMaterial(m_Material);
	m_Background->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
    m_Text = Swallow::Text::Create();
    m_Text->SetColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_Text->GetTransform()->SetScale(glm::vec3{1.0f, 2.0f, 1.0f});
    m_Text->GetTransform()->SetPosition(glm::vec3{-9.0f, -9.0f, 0.9f});
    m_Text->SetText("Bomberman");
    Recalculate();
}

Menu::Menu(Menu const &rhs)
{
    *this = rhs;
}

Menu &Menu::operator=(Menu const &rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}

Menu::~Menu()
{
    
}

void Menu::Recalculate()
{
    m_Background->GetTransform()->Recalculate();
    m_Text->Recalculate();
}

void Menu::RecalculateButtons()
{
    for (auto a: m_Buttons)
    {
        a->Recalculate();
    }
}

void Menu::AddButton(const char *text, float x, float y)
{
    m_Buttons.push_back(Button::Create(text, x, y));
    m_Buttons.back()->Recalculate();
}

void Menu::AddButton(const char *text, float x, float y, Swallow::OrthographicCamera &camera)
{
    m_Buttons.push_back(Button::Create(text, x, y, camera));
    m_Buttons.back()->Recalculate();
}
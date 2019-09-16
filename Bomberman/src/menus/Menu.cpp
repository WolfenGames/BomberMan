/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/16 16:51:58 by ppreez           ###   ########.fr       */
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
    m_Text->GetTransform()->SetPosition(glm::vec3{0.0f, 0.0f, 0.9f});
    // m_Text->SetText("Bomberman");
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
    m_Buttons.push_back(Button::Create());
    m_Buttons.back()->GetText()->SetText(text);
    m_Buttons.back()->GetText()->SetColour(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    m_Buttons.back()->GetText()->GetTransform()->SetPosition(glm::vec3{x, y, 0.8f});
    m_Buttons.back()->GetBackground()->GetTransform()->SetPosition(glm::vec3{x + 1.0f, y + 0.5f, 0.9f});
    m_Buttons.back()->GetBackground()->GetTransform()->SetScale(glm::vec3{1.0f, 1.5f, 1.0f});
}
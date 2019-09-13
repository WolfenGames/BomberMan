/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/13 14:12:19 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menu.hpp"

Menu::Menu()
{
    m_Material = MenuMaterial::Create();
    m_Material->SetColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_Background = Swallow::Primatives::Quad();
    m_Background->SetMaterial(m_Material);
    m_Background->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	m_Background->GetTransform()->SetScale(glm::vec3(10.0f, 10.0f, 0.0f));
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
    for (auto a : m_Buttons)
    {
        a.Recalculate();
    }
}
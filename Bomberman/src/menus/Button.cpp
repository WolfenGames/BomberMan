/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:37 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/16 16:13:15 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Button.hpp"

Button::Button()
:m_Pressed(false)
{
    m_Material = Swallow::MenuMaterial::Create();
    m_Background = Swallow::Primatives::Quad();
    m_Material->SetColour(glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});
    m_Background->SetMaterial(m_Material);
}

Button::Button(std::string text)
:m_Pressed(false)
{
    m_Text->SetText(text);
}

Button::Button(Button const &rhs)
{
    *this = rhs;
}

Button &Button::operator=(Button const &rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}

Button::~Button()
{

}

bool Button::Press()
{
    return true;
}

void Button::Recalculate()
{
    m_Background->GetTransform()->Recalculate();
    m_Text->Recalculate();
}
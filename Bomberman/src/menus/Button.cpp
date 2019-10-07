/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:37 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/07 16:38:30 by ppreez           ###   ########.fr       */
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

Button::Button(std::string text, float x, float y)
:m_Pressed(false), m_BackgroundX(x), m_BackgroundY(y), m_TextX(x), m_TextY(y)
{
    static_cast<void>(m_Pressed);
    m_Material = Swallow::MenuMaterial::Create();
    m_Background = Swallow::Primatives::Quad();
    m_Material->SetColour(glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});
    m_Background->SetMaterial(m_Material);

    GetText()->SetText(text);
    GetText()->SetColour(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    GetText()->GetTransform()->SetPosition(glm::vec3{x, y, 0.8f});
    GetText()->GetTransform()->SetScale(glm::vec3{0.8f, 1.5f, 1.0f});
    
    GetBackground()->GetTransform()->SetPosition(glm::vec3{x + (text.length() / 4.0f), y + 0.5f, 0.9f});
    GetBackground()->GetTransform()->SetScale(glm::vec3{text.length() / 4.0f, 1.0f, 1.0f});
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

void Button::SetBackgroundScale(float x, float y)
{
    GetBackground()->GetTransform()->SetScale(glm::vec3(x, y, 1.0f));
    GetBackground()->GetTransform()->SetPosition(glm::vec3(x + m_BackgroundX, y + m_BackgroundY, 1.0f));
}

// void Button::SetBackgroundPosition(float x, float y)
// {
// }

// void Button::SetTextScale(float x, float y)
// {

// }

// void Button::SetTextPosition(float x, float y)
// {
    
// }
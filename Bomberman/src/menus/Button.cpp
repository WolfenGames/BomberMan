/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:37 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/24 11:26:36 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Button.hpp"

Button::Button()
:Button("Sample text", 0, 0) 
{
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

    m_Text = Swallow::Text::Create();
    GetText()->SetText(text);
    GetText()->SetColour(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    GetText()->GetTransform()->SetPosition(glm::vec3{x, y, 0.8f});
    GetText()->GetTransform()->SetScale(glm::vec3{0.8f, 1.5f, 1.0f});
    
    GetBackground()->GetTransform()->SetPosition(glm::vec3{x + (text.length() / 4.0f), y + 0.5f, 0.9f});
    GetBackground()->GetTransform()->SetScale(glm::vec3{text.length() / 4.0f, 1.0f, 1.0f});
    Recalculate();
}

Button::Button(std::string text, float x, float y, Swallow::OrthographicCamera &camera)
:m_Pressed(false), m_BackgroundX(x), m_BackgroundY(y), m_TextX(x), m_TextY(y)
{
    static_cast<void>(m_Pressed);
    m_Material = Swallow::MenuMaterial::Create();
    m_Background = Swallow::Primatives::Quad();
    m_Material->SetColour(glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});
    m_Background->SetMaterial(m_Material);

    m_Text = Swallow::Text::Create();
    GetText()->SetText(text);
    GetText()->SetColour(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
    GetText()->GetTransform()->SetPosition(glm::vec3{x, y, 0.8f});
    GetText()->GetTransform()->SetScale(glm::vec3{0.8f, 1.5f, 1.0f});
    
    GetBackground()->GetTransform()->SetPosition(glm::vec3{x + (text.length() / 4.0f), y + 0.5f, 0.9f});
    GetBackground()->GetTransform()->SetScale(glm::vec3{text.length() / 4.0f, 1.0f, 1.0f});
    Recalculate();
    GenerateBackgroundDimensions(camera);
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

void Button::GenerateBackgroundDimensions(Swallow::OrthographicCamera &camera)
{
    glm::vec4 bl = GetBackground()->GetTransform()->GetModelMatrix() * glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
    glm::vec4 tr = GetBackground()->GetTransform()->GetModelMatrix() * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    m_BottomLeft = camera.WorldToScreenPoint(glm::vec3(bl.x, bl.y, bl.z));
    m_TopRight = camera.WorldToScreenPoint(glm::vec3(tr.x, tr.y, tr.z));

    m_BottomLeft.x = ((m_BottomLeft.x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	m_BottomLeft.y = ((m_BottomLeft.y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	m_TopRight.x = ((m_TopRight.x * 2) / Swallow::Application::Get().GetWindow().GetWidth()) - 1;
	m_TopRight.y = ((m_TopRight.y * 2) / Swallow::Application::Get().GetWindow().GetHeight()) - 1;
	SW_CORE_INFO("{} {}:{} {}", m_BottomLeft.x, m_BottomLeft.y, m_TopRight.x, m_TopRight.y);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:37 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/13 12:30:15 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Button.hpp"

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
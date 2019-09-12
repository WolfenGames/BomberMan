/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:54 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/12 16:08:01 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menu.hpp"

Menu::Menu()
:m_Material(MenuMaterial::Create())
{

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
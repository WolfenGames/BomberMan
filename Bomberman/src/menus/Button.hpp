/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:53 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/12 16:22:20 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
#include "Menu.hpp"

class Button: public Menu
{
    public:
        Button(std::string text);
        Button(Button const &rhs);
        Button &operator=(Button const &rhs);
        ~Button();

        bool Press();
    private:
        Button();
        bool m_Pressed;
        Swallow::Ref<Swallow::Text> m_Text;
        
};
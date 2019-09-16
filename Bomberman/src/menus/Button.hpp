/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:53 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/16 13:39:22 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
#include "Menu.hpp"

class Button: public Menu
{
    public:
        Button();
        Button(std::string text);
        Button(Button const &rhs);
        Button &operator=(Button const &rhs);
        ~Button();

        inline static Swallow::Ref<Button> Create() { return std::make_shared<Button>(); }
        bool Press();
        void SetText(std::string text);
        void Recalculate();
    private:
        bool m_Pressed;
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Button.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:58:53 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/17 09:14:34 by ppreez           ###   ########.fr       */
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
        Button(std::string text, float x, float y);
        Button(Button const &rhs);
        Button &operator=(Button const &rhs);
        ~Button();

        inline static Swallow::Ref<Button> Create() { return std::make_shared<Button>(); }
        inline static Swallow::Ref<Button> Create(std::string text, float x, float y) { return std::make_shared<Button>(text, x, y); }
        inline float GetBackgroundX() { return m_BackgroundX; }
        inline float GetBackgroundY() { return m_BackgroundY; }
        inline float GeTextX() { return m_TextX; }
        inline float GetTextY() { return m_TextY; }

        bool Press();
        void Recalculate();
        
        void SetBackgroundScale(float x, float y);
        // void SetBackgroundPosition(float x, float y);
        // void SetTextScale(float x, float y);
        // void SetTextPosition(float x, float y);
    private:
        bool m_Pressed;
        float m_BackgroundX;
        float m_BackgroundY;
        float m_TextX;
        float m_TextY;
};
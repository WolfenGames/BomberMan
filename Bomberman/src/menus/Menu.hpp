/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:47 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/27 16:19:38 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
#include "Swallow/Renderer/material/MaterialInstance.hpp"
#include "../material/MenuMaterial.hpp"
#include "Button.hpp"

// class Button;

class Menu
{
    public:
        Menu();
        Menu(Menu const &rhs);
        Menu &operator=(Menu const &rhs);
        ~Menu();

        inline static Swallow::Ref<Menu> Create() { return std::make_shared<Menu>(); }
        inline Swallow::Ref<Swallow::GameObject> GetBackground() { return m_Background; }
        inline Swallow::Ref<Swallow::Text> GetText() { return m_Text; }
        inline std::vector<Swallow::Ref<Button>> GetButtons() { return m_Buttons; }
        void Recalculate();
        void RecalculateButtons();
        void AddButton(const char *text, float x, float y);
        void AddButton(const char *text, float x, float y, Swallow::OrthographicCamera &camera);
    protected:
        Swallow::Ref<Swallow::FlatColourMaterialInstance> m_Material;
        Swallow::Ref<Swallow::GameObject> m_Background;
	    Swallow::Ref<Swallow::Text> m_Text;
        std::vector<Swallow::Ref<Button>> m_Buttons;
};
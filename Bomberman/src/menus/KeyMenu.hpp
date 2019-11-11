/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyMenu.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:55:36 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/11 11:24:36 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"

class KeyMenu: public MenuLayer
{
    public:
        KeyMenu();
        KeyMenu(const KeyMenu &rhs) = delete;
        KeyMenu &operator=(const KeyMenu &rhs) = delete;
        virtual ~KeyMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);

    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;
        size_t m_KeyCount;
        int m_Changed;
        bool m_InputActive;
        int m_ActiveButton;
        std::string m_InputAction;
};
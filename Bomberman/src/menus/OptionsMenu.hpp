/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionsMenu.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:33:12 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/24 15:39:48 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"

class OptionsMenu: public MenuLayer
{
    public:
        OptionsMenu();
        OptionsMenu(const OptionsMenu &rhs) = delete;
        OptionsMenu &operator=(const OptionsMenu &rhs) = delete;
        virtual ~OptionsMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);

    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;

};
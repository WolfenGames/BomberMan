/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PauseMenu.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:10:10 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/06 16:11:36 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"

class PauseMenu: public MenuLayer
{
    public:
        PauseMenu();
        PauseMenu(const PauseMenu &rhs) = delete;
        PauseMenu &operator=(const PauseMenu &rhs) = delete;
        virtual ~PauseMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);

    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;

};
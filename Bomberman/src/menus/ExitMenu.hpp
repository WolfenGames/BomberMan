/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExitMenu.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:31:19 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/25 16:32:10 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 
#include "../MenuLayer.hpp"

class ExitMenu: public MenuLayer
{
    public:
        ExitMenu();
        ExitMenu(const ExitMenu &rhs) = delete;
        ExitMenu &operator=(const ExitMenu &rhs) = delete;
        virtual ~ExitMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);

    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;

};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoadingMenu.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:44:28 by ppreez            #+#    #+#             */
/*   Updated: 2019/10/28 10:44:55 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"

class LoadingMenu: public MenuLayer
{
    public:
        LoadingMenu();
        LoadingMenu(const LoadingMenu &rhs) = delete;
        LoadingMenu &operator=(const LoadingMenu &rhs) = delete;
        virtual ~LoadingMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);

    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;
        bool m_InputActive;
        std::string m_Input;

};
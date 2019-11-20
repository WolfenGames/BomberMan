/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainMenu.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:26:27 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/06 16:11:49 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "../MenuLayer.hpp"
#include "OptionsMenu.hpp"
#include "ExitMenu.hpp"
#include "LoadMenu.hpp"
#include "KeyMenu.hpp"
#include "NewGame.hpp"
#include "PauseMenu.hpp"

class MainMenu: public MenuLayer
{
    public:
        MainMenu();
        MainMenu(const MainMenu &rhs) = delete;
        MainMenu &operator=(const MainMenu &rhs) = delete;
        virtual ~MainMenu() = default;

        void OnEvent(Swallow::Event &e) override;
        bool OnMouseButtonPressed(Swallow::MouseButtonPressedEvent &e);
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);
        bool OnMouseMovedEvent(Swallow::MouseMovedEvent &e);
    private:
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;

};
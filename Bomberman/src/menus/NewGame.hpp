/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NewGame.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:57:22 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/08 16:05:15 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"

class NewGame: public MenuLayer
{
    public:
        NewGame();
        NewGame(const NewGame &rhs) = delete;
        NewGame &operator=(const NewGame &rhs) = delete;
        virtual ~NewGame() = default;

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
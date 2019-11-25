/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HudMenu.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:16:18 by ppreez            #+#    #+#             */
/*   Updated: 2019/11/20 14:11:20 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../MenuLayer.hpp"
 
class HudMenu: public MenuLayer
{
    public:
        HudMenu();
        HudMenu(const HudMenu &rhs) = delete;
        HudMenu &operator=(const HudMenu &rhs) = delete;
        virtual ~HudMenu() = default;
        
        void OnEvent(Swallow::Event &e) override;
        bool OnKeyPressed(Swallow::KeyPressedEvent &e);
	    virtual void OnUpdate(Swallow::Timestep ts) override;
    private:
        void UpdateButtons();
    	Swallow::OrthographicCamera m_Camera;
    	glm::ivec2	map_size;

};
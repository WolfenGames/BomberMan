/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Menu.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:48:47 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/12 16:09:34 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Swallow/Renderer/material/MaterialInstance.hpp"
#include "Bomberman/src/material/MenuMaterial.hpp"

class Menu
{
    public:
        Menu();
        Menu(Menu const &rhs);
        Menu &operator=(Menu const &rhs);
        ~Menu();
    private:
        Ref<Swallow::MaterialInstance> m_Material;
        std::vector<Menu> m_Buttons;
};
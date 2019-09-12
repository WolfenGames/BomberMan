/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MenuMaterial.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:58:45 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/12 16:21:00 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
// #include "Swallow/Renderer/material/FlatColourMaterial.hpp"

class MenuMaterial
{
    public:
        static void Init();
        static Swallow::Ref<Swallow::FlatColourMaterialInstance> Create();
    private:
        static Swallow::Ref<Swallow::Shader> m_Shader;
};
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MenuMaterial.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:00:05 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/13 12:32:52 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Swallow/swpch.hpp"
#include "MenuMaterial.hpp"

namespace Swallow
{
    Ref<Shader> m_Shader;

    void MenuMaterial::Init()
    {
        m_Shader = Swallow::Shader::Create("assets/shaders/MenuColour.glsl");
    }

    Ref<FlatColourMaterialInstance> MenuMaterial::Create()
    {
		  return std::make_shared<FlatColourMaterialInstance>(m_Shader);
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MenuMaterial.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <ppreez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:58:45 by ppreez            #+#    #+#             */
/*   Updated: 2019/09/16 12:46:03 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <Swallow.hpp>
#include "Swallow/Renderer/material/FlatColourMaterial.hpp"

namespace Swallow
{
    class MenuMaterial
    {
        public:
            static void Init();
            static Ref<FlatColourMaterialInstance> Create();
        private:
            static Ref<Shader> m_Shader;
    };
}
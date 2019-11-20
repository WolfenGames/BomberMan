

#pragma once

#include <Swallow.hpp>
#include "Swallow/Renderer/texture/TextureMaterial.hpp"


namespace Swallow
{
    class MenuBackgroundMaterial
    {
        public:
            static void Init();
            static Ref<TextureMaterialInstance> Create();
        private:
            static Ref<Shader> m_Shader;
    };
}
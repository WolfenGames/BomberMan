#include "swpch.hpp"
#include "MenuBackgroundMaterial.hpp"

namespace Swallow
{
    Ref<Shader> MenuBackgroundMaterial::m_Shader;

    void MenuBackgroundMaterial::Init()
    {
        m_Shader = Shader::Create("assets/shaders/MenuTextureColour.glsl");
    }

    Ref<TextureMaterialInstance> MenuBackgroundMaterial::Create()
    {
        return std::make_shared<TextureMaterialInstance>(m_Shader);
    }
}
#include "Flame.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Flame::Flame()
{
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Brick = Swallow::FlatColourMaterial::Create();
	Brick->SetColour(glm::vec4(1.0, 0.2, 0.2, 1.0));
	SetMaterial(Brick);
	GetTransform()->SetScale(glm::vec3(0.3));
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomb", "Bomb"));

	duration = 1.0f;
}
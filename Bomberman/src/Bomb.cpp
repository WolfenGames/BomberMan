#include "Bomb.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Bomb::Bomb()
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> Bomb = Swallow::FlatColourMaterial::Create();
	Bomb->SetColour({0.0f, 0.0f, 0.0f, 1.0f});
	SetDestructable(false);
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomb", "Bomb"));
	SetMaterial(Bomb);
	GetTransform()->SetScale(glm::vec3(0.5f));
	GetTransform()->Recalculate();
	m_isFilled = true;
}
#include "Wall.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Wall::Wall()
{
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Brick = Swallow::FlatColourMaterial::Create();
	Brick->SetColour(glm::vec4(0.9, 0.5, 0.2, 1.0));
	SetMaterial(Brick);
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomb", "Bomb"));

	m_isDestructable = true;
	m_isFilled = true;
	m_isExit = false;
}

Pillar::Pillar()
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> Pillar = Swallow::FlatColourMaterial::Create();
	Pillar->SetColour(glm::vec4(0.5, 0.5, 0.5, 1.0));
	SetMaterial(Pillar);
	SetVertexArray(Swallow::AssetManager::FetchObject("Bomb", "Bomb"));

	m_isDestructable = false;
	m_isFilled = true;
	m_isExit = false;
}
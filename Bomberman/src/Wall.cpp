#include "Wall.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include <Swallow/Renderer/texture/TextureMaterial.hpp>

//Destructable walls
Wall::Wall()
{
	/*
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Brick = Swallow::FlatColourMaterial::Create();
	Brick->SetColour(glm::vec4(0.9, 0.5, 0.2, 1.0));
	SetMaterial(Brick);
	*/

	Swallow::Ref<Swallow::TextureMaterialInstance> Brick = Swallow::TextureMaterial::Create();
	Brick->SetTexture(Swallow::AssetManager::FetchTexture("Atlas"));
	SetMaterial(Brick);

	SetVertexArray(Swallow::AssetManager::FetchObject("DestructableWall", "Destructable_Wall.001"));
	GetTransform()->SetScale(glm::vec3(0.95f));

	m_isDestructable = true;
	m_isFilled = true;
	m_isExit = false;
	m_canPassThrough = true;
}

//Indestructable walls
Pillar::Pillar()
{
	Swallow::Ref<Swallow::TextureMaterialInstance> Pillar = Swallow::TextureMaterial::Create();
	Pillar->SetTexture(Swallow::AssetManager::FetchTexture("Atlas"));
	SetMaterial(Pillar);

	SetVertexArray(Swallow::AssetManager::FetchObject("IndestructableWall", "Indestructable_Wall.001"));
	GetTransform()->SetScale(glm::vec3(1.0f));
	
	m_isDestructable = false;
	m_isFilled = true;
	m_isExit = false;
	m_canPassThrough = false;
}

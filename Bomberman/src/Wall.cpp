#include "Wall.hpp"
#include <Swallow/Renderer/material/FlatColourMaterial.hpp>

Wall::Wall()
{
	Swallow::Ref<Swallow::FlatColourMaterialInstance> Brick = Swallow::FlatColourMaterial::Create();
	Brick->SetColour(glm::vec4(0.9, 0.5, 0.2, 1.0));
	SetMaterial(Brick);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.95f));

	m_isDestructable = true;
	m_isFilled = true;
	m_isExit = false;
	m_canPassThrough = true;
}

Pillar::Pillar()
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> Pillar = Swallow::FlatColourMaterial::Create();
	Pillar->SetColour(glm::vec4(0.5, 0.5, 0.5, 1.0));
	SetMaterial(Pillar);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(0.95f));

	m_isDestructable = false;
	m_isFilled = true;
	m_isExit = false;
	m_canPassThrough = false;
}

LevelExit::LevelExit()
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> LevelExit = Swallow::FlatColourMaterial::Create();
	LevelExit->SetColour(glm::vec4(0.f, 0.f, 1.f, 1.f));
	SetMaterial(LevelExit);
	SetVertexArray(Swallow::AssetManager::FetchObject("Cube", "Cube"));
	GetTransform()->SetScale(glm::vec3(1.f, 0.5f, .2f));

	m_isDestructable = false;
	m_isFilled = true;
	m_isExit = true;
}

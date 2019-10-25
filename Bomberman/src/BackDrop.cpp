#include "swpch.hpp"

#include "BackDrop.hpp"

#include <Swallow/Renderer/material/FlatColourMaterial.hpp>
#include <Swallow/Renderer/texture/TextureMaterial.hpp>

BackDrop::BackDrop(const glm::vec3 pos)
{
	static Swallow::Ref<Swallow::FlatColourMaterialInstance> mat = Swallow::FlatColourMaterial::Create();
	mat->SetColour(glm::vec4((88.f/255.f), (210.f/255.f), (255.f/255.f), 1.0f));
	SetMaterial(mat);
	SetVertexArray(Swallow::AssetManager::FetchObject("EmptyQuad", "EmptyQuad"));
	// SetVertexArray(Swallow::AssetManager::FetchObject("Bomberman", "Bomberman"));
	GetTransform()->SetScale(glm::vec3(10.f));
	GetTransform()->SetRotation(glm::vec3(glm::radians(90.f), 0, 0));
	GetTransform()->SetPosition(pos);
	GetTransform()->Recalculate();
	m_pos = GetTransform()->GetPosition();
}
BackDrop::~BackDrop(){}
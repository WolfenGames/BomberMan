#pragma once

#include <Swallow.hpp>
#include "Swallow/Renderer/material/AnimationMaterial.hpp"

class Level;

class Enemy : public Swallow::GameObject, public ModelInfo
{
public:
	Enemy(const glm::vec3&, Swallow::Ref<Level> l);
	Enemy(const Enemy&) = default;
	Enemy& operator=(const Enemy&) = default;
	
	void makeDecision();
	glm::vec3& Destination();
	void Update(Swallow::Timestep ts);
	inline bool CanDelete() { return m_Delete; }
	inline void SetDelete(bool b) { m_Delete = b; }

	~Enemy();

private:
	glm::vec3											m_Destination;
	Swallow::Ref<Level>									m_Level;
	Swallow::Ref<Swallow::GameObject>					m_Cube;
	glm::vec3											m_MoveDir;
	bool												m_Delete = false;
	Swallow::Ref<Swallow::AnimationMaterialInstance> 	animMaterial;

protected:
	Enemy() = default;

};
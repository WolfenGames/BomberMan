#pragma once

#include <Swallow.hpp>
#include "Level.hpp"

class Enemy : public Swallow::GameObject
{
public:
	Enemy(const glm::vec3&, Level&);
	Enemy(const Enemy&) = default;
	Enemy& operator=(const Enemy&) = default;
	
	void makeDecision();
	glm::vec3& Destination();
	void Update(Swallow::Timestep ts);

	~Enemy();

private:
	glm::vec3							m_Pos;
	Level								&m_Level;
	uint32_t							m_MaxMoves;
	Swallow::Ref<Swallow::GameObject>	m_Cube;
	glm::vec2							m_MoveDir;

protected:
	Enemy() = default;

};